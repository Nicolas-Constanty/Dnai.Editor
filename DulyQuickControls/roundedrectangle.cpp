#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "roundedrectangle.h"

RoundedRectangle::RoundedRectangle(QQuickItem *parent) : QQuickItem(parent), m_roundedSegments(5)
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


QSGNode *RoundedRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    qDebug() << "YAY";
    QSGNode *node = 0;
//    QSGGeometry *geometry = 0;

    node = new QSGNode;
//    geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4 * 5);
//    geometry->setLineWidth(1);
//    geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
//    node->setGeometry(geometry);
//    node->setFlag(QSGNode::OwnsGeometry);
//    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
//    material->setColor(QColor(255, 0, 0));
//    node->setMaterial(material);
//    node->setFlag(QSGNode::OwnsMaterial);

    QSGGeometryNode *buffer = new QSGGeometryNode;
    QSGGeometry *bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 0, 0));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::Point2D *vertices = bufferGeometry->vertexDataAsPoint2D();
    //Center
    vertices[0].set(- width() , - height());
    vertices[1].set(- width(), height());
    vertices[2].set(width(), - height());
    vertices[3].set(width(), height());
    node->appendChildNode(buffer);

    if (m_radius <= 0)
        return node;
    //Top
    buffer = new QSGGeometryNode;
    bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    material = new QSGFlatColorMaterial;
    material->setColor(QColor(0, 255, 0));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    vertices = bufferGeometry->vertexDataAsPoint2D();
    vertices[0].set(- width() , - height() - m_radius);
    vertices[1].set(- width(), -height());
    vertices[2].set(width(), - height() - m_radius);
    vertices[3].set(width(),- height());
    node->appendChildNode(buffer);

    //Bottom
    buffer = new QSGGeometryNode;
    bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    material = new QSGFlatColorMaterial;
    material->setColor(QColor(0, 0, 255));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    vertices = bufferGeometry->vertexDataAsPoint2D();
    vertices[0].set(- width() , height());
    vertices[1].set(- width(), height() + m_radius);
    vertices[2].set(width(), height());
    vertices[3].set(width(), height() + m_radius);
    node->appendChildNode(buffer);

    //Left
    buffer = new QSGGeometryNode;
    bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 255, 0));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    vertices = bufferGeometry->vertexDataAsPoint2D();
    vertices[0].set(- width() - m_radius, - height());
    vertices[1].set(- width() - m_radius, height());
    vertices[2].set(-width(), - height());
    vertices[3].set(-width(), height());
    node->appendChildNode(buffer);

    //Right
    buffer = new QSGGeometryNode;
    bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    material = new QSGFlatColorMaterial;
    material->setColor(QColor(255, 0, 255));
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    vertices = bufferGeometry->vertexDataAsPoint2D();
    vertices[0].set(width() , - height());
    vertices[1].set(width(), height());
    vertices[2].set(width() + m_radius, - height());
    vertices[3].set(width() + m_radius, height());
    node->appendChildNode(buffer);

    node->appendChildNode(DrawCorner(Corner::TopLeft));
    node->appendChildNode(DrawCorner(Corner::TopRight));
    node->appendChildNode(DrawCorner(Corner::BottomLeft));
    node->appendChildNode(DrawCorner(Corner::BottomRight));
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

    double offset;
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
    double a = qDegreesToRadians(90.0 / m_roundedSegments);

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
