#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "roundedrectangle.h"

RoundedRectangle::RoundedRectangle(QQuickItem *parent) :
    QQuickItem(parent),
    m_roundedSegments(5),
    m_topLeft(true),
    m_topRight(true),
    m_bottomLeft(true),
    m_bottomRight(true)
{
    setFlag(ItemHasContents, true);
}

void RoundedRectangle::setRoundedSegments(int segments)
{
    if (segments == m_roundedSegments)
        return;
    m_roundedSegments = segments;
    emit roundedSegmentsChanged(segments);
    update();
}

void RoundedRectangle::setRadius(double radius)
{
    if (radius == m_radius)
        return;
    m_radius = radius;
    emit radiusChanged(radius);
    update();
}

void RoundedRectangle::setTopLeft(bool value)
{
    if (value == m_topLeft)
        return;
    m_topLeft = value;
    emit topLeftChanged(value);
    update();
}

void RoundedRectangle::setTopRight(bool value)
{
    if (value == m_topRight)
        return;
    m_topRight = value;
    emit topRightChanged(value);
    update();
}

void RoundedRectangle::setBottomLeft(bool value)
{
    if (value == m_bottomLeft)
        return;
    m_bottomLeft = value;
    emit bottomLeftChanged(value);
    update();
}

void RoundedRectangle::setBottomRight(bool value)
{
    if (value == m_bottomRight)
        return;
    m_bottomRight = value;
    emit bottomRightChanged(value);
    update();
}

int RoundedRectangle::GetNumberRoundedCorner() const
{
    int count = 0;
    if (m_topLeft)
        ++count;
    if (m_topRight)
        ++count;
    if (m_bottomLeft)
        ++count;
    if (m_bottomRight)
        ++count;
    return count;
}


QSGNode *RoundedRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
	QSGNode *node = new QSGNode;

    QSGGeometryNode *buffer = new QSGGeometryNode;
    const int nCorner = GetNumberRoundedCorner();
    qDebug() << 20 /* 4 * 5 squares */ + (2 * m_roundedSegments + 2) * nCorner;
    QSGGeometry *bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 20 /* 4 * 5 squares */ + (2 * m_roundedSegments + 2) * nCorner - nCorner - 1);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 0, 0));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::Point2D *vertices = bufferGeometry->vertexDataAsPoint2D();
    int idx = -1;
    const double a = qDegreesToRadians(90.0 / m_roundedSegments);
    for (int i = 0; i < 4 +  (2 * m_roundedSegments + 2) * nCorner; i++)
    {
        vertices[i].set(0,0);
    }
    if (m_topLeft)
    {
        QPointF center;
        center.setX(- width());
        center.setY(- height());
        const double offset = (M_PI / 2.0) * 2.0;
        for (int i = 0; i < m_roundedSegments; i++)
        {
            vertices[++idx].set(center.x(), center.y());
            vertices[++idx].set( center.x() + m_radius * qCos(a * i + offset), center.y() + m_radius * qSin(a * i + offset));
        }
        vertices[++idx].set(center.x(), center.y());
    }

    //Top
    vertices[++idx].set(-width() + ((m_topLeft)?0:-m_radius), - height() - m_radius);
    vertices[++idx].set(width() + ((m_topRight)?0:m_radius), - height() - m_radius);
    vertices[++idx].set(-width() + ((m_topLeft)?0:-m_radius), - height());
    vertices[++idx].set(width() + ((m_topRight)?0:m_radius), - height());

    if (m_topRight)
    {
        QPointF center;
        center.setX(width());
        center.setY(- height());
        const double offset = (M_PI / 2) * 3;
        for (int i = 0; i < m_roundedSegments; i++)
        {
            vertices[++idx].set(center.x(), center.y());
            vertices[++idx].set( center.x() + m_radius * qCos(a * i + offset), center.y() + m_radius * qSin(a * i + offset));
        }
        vertices[++idx].set(center.x(), center.y());
    }
    //Right
    vertices[++idx].set(width() + m_radius, - height());
    vertices[++idx].set(width() + m_radius, height());
    vertices[++idx].set(width(), - height());
    vertices[++idx].set(width(), height());

    if (m_bottomRight)
    {
        QPointF center;
        center.setX(width());
        center.setY(height());
        for (int i = 0; i < m_roundedSegments; i++)
        {
            vertices[++idx].set(center.x(), center.y());
            vertices[++idx].set( center.x() + m_radius * qCos(a * i), center.y() + m_radius * qSin(a * i));
        }
        vertices[++idx].set(center.x(), center.y());
    }

    //Bottom
    vertices[++idx].set(width() + ((m_bottomRight)?0:m_radius), height() + m_radius);
    vertices[++idx].set(-width() + ((m_bottomLeft)?0:-m_radius), height() + m_radius);
    vertices[++idx].set(width() + ((m_bottomRight)?0:m_radius), height());
    vertices[++idx].set(-width() + ((m_bottomLeft)?0:-m_radius), height());

    if (m_bottomLeft)
    {
        QPointF center;
        center.setX(- width());
        center.setY(height());
        const double offset = (M_PI / 2.0);
        for (int i = 0; i < m_roundedSegments; i++)
        {
            vertices[++idx].set(center.x(), center.y());
            vertices[++idx].set( center.x() + m_radius * qCos(a * i + offset), center.y() + m_radius * qSin(a * i + offset));
        }
        vertices[++idx].set(center.x(), center.y());
    }

    //Left
    vertices[++idx].set(-width() - m_radius, height());
    vertices[++idx].set(-width() - m_radius, -height());
    vertices[++idx].set(-width(), height());
    vertices[++idx].set(-width(), - height());

    vertices[++idx].set(width(), -height());
    vertices[++idx].set(-width(), height());
    vertices[++idx].set(width(), height());

//    vertices[++idx].set(-width() + ((m_topLeft)?0:-m_radius), - height());
//    vertices[++idx].set(width() + ((m_topRight)?0:m_radius), - height());
    qDebug() << idx;
//    vertices[++idx].set(width() + ((m_topRight)?0:m_radius),- height());
//    vertices[++idx].set(- width() + ((m_topLeft)?0:-m_radius), - height() - m_radius);
//    vertices[++idx].set(width()+ ((m_topRight)?0:m_radius), - height() - m_radius);
//    vertices[++idx].set(- width() + ((m_topLeft)?0:-m_radius), - height());



    return buffer;
    //Center
//    if (!m_topLeft && !m_topRight)
//    {
//        vertices[0].set(- width() - m_radius, - height() - m_radius);
//        vertices[1].set(- width() - m_radius, height());
//        vertices[2].set(width() + m_radius, - height() - m_radius);
//        vertices[3].set(width() + m_radius, height());
//    }
//    else
//    {
//        vertices[0].set(- width() , - height());
//        vertices[1].set(- width(), height());
//        vertices[2].set(width(), - height());
//        vertices[3].set(width(), height());
//    }
//    node->appendChildNode(buffer);

//    if (m_radius <= 0)
//        return node;
//    //Top
//    if (m_topLeft || m_topRight)
//    {
//        buffer = new QSGGeometryNode;
//        bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
//        bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
//        buffer->setGeometry(bufferGeometry);
//        buffer->setFlag(QSGNode::OwnsGeometry);
//        material = new QSGFlatColorMaterial;
//        material->setColor(QColor(0, 255, 0));
//        buffer->setMaterial(material);
//        buffer->setFlag(QSGNode::OwnsMaterial);

//        vertices = bufferGeometry->vertexDataAsPoint2D();
//        vertices[0].set(- width() + ((m_topLeft)?0:-m_radius), - height() - m_radius);
//        vertices[1].set(- width() + ((m_topLeft)?0:-m_radius), - height());
//        vertices[2].set(width()+ ((m_topRight)?0:m_radius), - height() - m_radius);
//        vertices[3].set(width()+ ((m_topRight)?0:m_radius),- height());
//        node->appendChildNode(buffer);
//    }

//    //Bottom
//    buffer = new QSGGeometryNode;
//    bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
//    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
//    buffer->setGeometry(bufferGeometry);
//    buffer->setFlag(QSGNode::OwnsGeometry);
//    material = new QSGFlatColorMaterial;
//    material->setColor(QColor(0, 0, 255));
//    buffer->setMaterial(material);
//    buffer->setFlag(QSGNode::OwnsMaterial);

//    vertices = bufferGeometry->vertexDataAsPoint2D();
//    vertices[0].set(- width() , height());
//    vertices[1].set(- width(), height() + m_radius);
//    vertices[2].set(width(), height());
//    vertices[3].set(width(), height() + m_radius);
//    node->appendChildNode(buffer);

//    if (m_topLeft && m_topRight)
//    {
//        //Left
//        buffer = new QSGGeometryNode;
//        bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
//        bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
//        buffer->setGeometry(bufferGeometry);
//        buffer->setFlag(QSGNode::OwnsGeometry);
//        material = new QSGFlatColorMaterial;
//        material->setColor(QColor(255, 255, 0));
//        buffer->setMaterial(material);
//        buffer->setFlag(QSGNode::OwnsMaterial);

//        vertices = bufferGeometry->vertexDataAsPoint2D();
//        vertices[0].set(- width() - m_radius, - height());
//        vertices[1].set(- width() - m_radius, height());
//        vertices[2].set(-width(), - height());
//        vertices[3].set(-width(), height());
//        node->appendChildNode(buffer);

//        //Right
//        buffer = new QSGGeometryNode;
//        bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
//        bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
//        buffer->setGeometry(bufferGeometry);
//        buffer->setFlag(QSGNode::OwnsGeometry);
//        material = new QSGFlatColorMaterial;
//        material->setColor(QColor(255, 0, 255));
//        buffer->setMaterial(material);
//        buffer->setFlag(QSGNode::OwnsMaterial);

//        vertices = bufferGeometry->vertexDataAsPoint2D();
//        vertices[0].set(width() , - height());
//        vertices[1].set(width(), height());
//        vertices[2].set(width() + m_radius, - height());
//        vertices[3].set(width() + m_radius, height());
//        node->appendChildNode(buffer);
//    }


//    if (m_topLeft)
//        node->appendChildNode(DrawCorner(Corner::TopLeft));
//    if (m_topRight)
//        node->appendChildNode(DrawCorner(Corner::TopRight));
//    node->appendChildNode(DrawCorner(Corner::BottomLeft));
//    node->appendChildNode(DrawCorner(Corner::BottomRight));
    return node;
}

QSGGeometryNode *RoundedRectangle::DrawCorner(Corner type)
{
    QSGGeometryNode *buffer = new QSGGeometryNode;
    QSGGeometry *bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_roundedSegments + 2);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(128, 0, 255));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::Point2D *vertices = bufferGeometry->vertexDataAsPoint2D();

	double offset = 0;
    QPointF center;
    switch (type) {
        case Corner::TopLeft:
            center.setX(- width());
            center.setY(- height());
            offset = (M_PI / 2) * 2;
            break;
        case Corner::TopRight:
            center.setX(width());
            center.setY(- height());
            offset = (M_PI / 2) * 3;
            break;
        case Corner::BottomLeft:
            center.setX(- width());
            center.setY(height());
            offset = (M_PI / 2);
            break;
        case Corner::BottomRight:
            center.setX(width());
            center.setY(height());
            offset = 0;
            break;
    }
	const double a = qDegreesToRadians(90.0 / m_roundedSegments);

    vertices[0].set(center.x(), center.y());
    for (int i = 1; i < m_roundedSegments + 1; i++)
    {
        vertices[i].set( center.x() + m_radius * qCos(a * (i -1) + offset), center.y() + m_radius * qSin(a * (i - 1) + offset));
    }
    switch (type) {
        case Corner::TopLeft:
            vertices[m_roundedSegments + 1].set(- width(), -height() - m_radius);
            break;
        case Corner::TopRight:
            vertices[m_roundedSegments + 1].set(width() + m_radius, -height());
            break;
        case Corner::BottomLeft:
            vertices[m_roundedSegments + 1].set(-width() - m_radius, height());
            break;
        case Corner::BottomRight:
            vertices[m_roundedSegments + 1].set(width(), height() + m_radius);
            break;
    }
    return buffer;
}
