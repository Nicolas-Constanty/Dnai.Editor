#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "roundedrectangle.h"
#include "dulycanvas.h"

RoundedRectangle::RoundedRectangle(QQuickItem *parent) :
    CustomShape(parent)
    , m_topLeft(true)
    , m_topRight(true)
    , m_bottomLeft(true)
    , m_bottomRight(true)
    , m_nbSegments(5)
{
    setFlag(ItemHasContents, true);
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

void RoundedRectangle::setRoundedSegments(uint segments)
{
    if (segments == m_nbSegments)
        return;
    m_nbSegments = segments;
    emit roundedSegmentsChanged(segments);
    update();
}

int RoundedRectangle::getNumberRoundedCorner() const
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

QSGGeometryNode *RoundedRectangle::createBorder() const
{
    int idx = -1;
    const qreal h = (height() - m_radius * 2.f) / 2.f;
    const qreal w = (width() - m_radius * 2.f) / 2.f;
    const float a = 0.5f * float(M_PI) / m_nbSegments;
    const bool aa = antialiasing();
    const int nCorner = getNumberRoundedCorner();
    const uint aaoffset = 1;
    const uchar r = m_borderColor.red();
    const uchar g = m_borderColor.green();
    const uchar b = m_borderColor.blue();
    const uchar alpha = m_borderColor.alpha();
    const uint nbVertice = (aa ? (m_nbSegments % 2 == 0 ? (7.5 * m_nbSegments) : (7.5 * (m_nbSegments-1)+8) ) : m_nbSegments) * nCorner + (aa?7*4+(m_topLeft?0:1):8) + (aa?0:-nCorner);
    const QPointF center(w + m_radius, h + m_radius);

    QSGGeometryNode *nodeBorder = new QSGGeometryNode;
    QSGVertexColorMaterial *materialBorder = new QSGVertexColorMaterial;
    QSGGeometry *nodeBorderGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertice);
    if (!aa)
        nodeBorderGeometry->setLineWidth(m_borderWidth);
    nodeBorderGeometry->setDrawingMode(aa ? QSGGeometry::DrawTriangleStrip : QSGGeometry::DrawLineStrip);
    nodeBorder->setGeometry(nodeBorderGeometry);
    nodeBorder->setFlag(QSGNode::OwnsGeometry, aa);
    materialBorder->setFlag(QSGMaterial::Blending);

    nodeBorder->setMaterial(materialBorder);

    QSGGeometry::ColoredPoint2D *vertices = nodeBorderGeometry->vertexDataAsColoredPoint2D();
    if (!aa)
    {
	    const auto drawCircle = [&](qreal cx, qreal cy, float offset)
        {
            for (uint i = 0; i < m_nbSegments; i++)
                vertices[++idx].set( cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
        };
        if (m_topLeft)
            drawCircle(-w + center.x(), -h + center.y(), float(M_PI));
        else
            vertices[++idx].set(-w + center.x()-m_radius, -h + center.y() - m_radius, r, g, b, alpha);
        vertices[++idx].set(w + center.x(), -h + center.y() - m_radius, r, g, b, alpha);
        if (m_topRight)
            drawCircle(w + center.x(), -h + center.y(), (float(M_PI) / 2.f) * 3.f);
        else
            vertices[++idx].set(w + center.x() + m_radius, -h + center.y() -m_radius, r, g, b, alpha);

        vertices[++idx].set(w + center.x() + m_radius, h + center.y(), r, g, b, alpha);
        if (m_bottomRight)
            drawCircle(w + center.x(), h + center.y(), 0);
        else
            vertices[++idx].set(w + center.x() + m_radius, h + center.y() + m_radius, r, g, b, alpha);
        vertices[++idx].set(-w + center.x(), h + center.y() + m_radius, r, g, b, alpha);
        if (m_bottomLeft)
            drawCircle(-w + center.x(), h + center.y(), float(M_PI) / 2.0f);
        else
            vertices[++idx].set(-w + center.x() - m_radius, h + center.y() + m_radius, r, g, b, alpha);
        vertices[++idx].set(-w + center.x() -m_radius, -h + center.y() + ((m_topLeft)?0:- m_radius), r, g, b, alpha);
    }
    else
    {
        const qreal mid = m_borderWidth / 2.f;
	    const auto drawCircle = [&](qreal cx, qreal cy, float offset, bool dir = true)
        {
            for (uint i = 0; i < m_nbSegments; i++)
            {
                if ((i % 2 == 0 && dir) || (!dir && i % 2 != 0))
                {
                    //Inner
                    vertices[++idx].set( cx + (m_radius - mid - aaoffset) * qFastCos(a * i + offset), cy + (m_radius - mid - aaoffset) * qFastSin(a * i + offset), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
                    vertices[++idx].set( cx + (m_radius - mid - aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius - mid - aaoffset) * qFastSin(a * (i + 1) + offset), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

                    //Mid
                    vertices[++idx].set( cx + (m_radius - mid) * qFastCos(a * i + offset), cy + (m_radius - mid) * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius - mid) * qFastCos(a * (i + 1) + offset), cy + (m_radius - mid) * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius + mid) * qFastCos(a * i + offset), cy + (m_radius + mid) * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius + mid) * qFastCos(a * (i + 1) + offset), cy + (m_radius + mid) * qFastSin(a * (i + 1) + offset), r, g, b, alpha);

                    //Outer
                    vertices[++idx].set( cx + (m_radius + mid + aaoffset) * qFastCos(a * i + offset), cy + (m_radius + mid + aaoffset) * qFastSin(a * i + offset), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + mid + aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius + mid + aaoffset) * qFastSin(a * (i + 1) + offset), 0, 0, 0, 0);
                }
                else if ((i % 2 == 0 && !dir) || dir)
                {
                    //Outer
                    vertices[++idx].set( cx + (m_radius + mid + aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius + mid + aaoffset) * qFastSin(a * (i + 1) + offset), 0, 0, 0, 0);

                    //Center
                    vertices[++idx].set( cx + (m_radius + mid) * qFastCos(a * i + offset), cy + (m_radius + mid) * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius + mid) * qFastCos(a * (i + 1) + offset), cy + (m_radius + mid) * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius - mid) * qFastCos(a * i + offset), cy + (m_radius - mid) * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius - mid) * qFastCos(a * (i + 1) + offset), cy + (m_radius - mid) * qFastSin(a * (i + 1) + offset), r, g, b, alpha);

                    //Inner
                    vertices[++idx].set( cx + (m_radius - mid - aaoffset) * qFastCos(a * i + offset), cy + (m_radius - mid - aaoffset) * qFastSin(a * i + offset), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
                    vertices[++idx].set( cx + (m_radius - mid - aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius - mid - aaoffset) * qFastSin(a * (i + 1) + offset), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
                }
            }
        };

        if (m_topLeft)
            drawCircle(-w + center.x(), -h + center.y(), float(M_PI));
        else
            vertices[++idx].set(-w + center.x() + mid + aaoffset - m_radius, -h + center.y() - m_radius + mid + aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(w + center.x() + (m_topRight?0:-mid - aaoffset + m_radius), -h + center.y() - m_radius + mid + aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        //Center
        vertices[++idx].set(-w + center.x() + (m_topLeft?0:mid - m_radius), -h + center.y() - m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(w + center.x() + (m_topRight?0:mid  + m_radius), -h + center.y() - m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(-w + center.x() + (m_topLeft?0:-mid - m_radius), -h + center.y() - m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(w + center.x() + (m_topRight?0:mid + m_radius), -h + center.y() - m_radius - mid, r, g, b, alpha);

        //Outer
        vertices[++idx].set(-w + center.x() + (m_topLeft?0:-mid - aaoffset - m_radius), -h + center.y() - m_radius - mid - aaoffset, 0, 0, 0, 0);
        vertices[++idx].set(w + center.x() + (m_topRight?0:mid + aaoffset + m_radius), -h + center.y() - m_radius - mid - aaoffset, 0, 0, 0, 0);

        if (m_topRight)
            drawCircle(w + center.x(), -h + center.y(), (float(M_PI) / 2.f) * 3.f, false);

        //Outer
        vertices[++idx].set(w + center.x() + m_radius + mid + aaoffset, h + center.y() + (m_bottomRight?0:mid + aaoffset + m_radius), 0, 0, 0, 0);

        //Center
        vertices[++idx].set(w + center.x() + m_radius + mid, -h + center.y() + (m_topRight?0:-mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(w + center.x() + m_radius + mid, h + center.y() + (m_bottomRight?0:mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(w + center.x() + m_radius - mid, -h + center.y() + (m_topRight?0:mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(w + center.x() + m_radius - mid, h + center.y() + (m_bottomRight?0:-mid + m_radius), r, g, b, alpha);

        //Inner
        vertices[++idx].set(w + center.x() + m_radius - mid - aaoffset, -h + center.y() + (m_topRight?0:mid + aaoffset - m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(w + center.x() + m_radius - mid - aaoffset, h + center.y() + (m_bottomRight?0:-mid - aaoffset + m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        if (m_bottomRight)
            drawCircle(w + center.x(), h + center.y(), 0);

        //Inner
        vertices[++idx].set(-w + center.x() + (m_bottomLeft?0:mid + aaoffset - m_radius), h + center.y() + m_radius - mid - aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        //Center
        vertices[++idx].set(w + center.x() + (m_bottomRight?0:-mid + m_radius), h + center.y() + m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(-w + center.x() + (m_bottomLeft?0:mid - m_radius), h + center.y() + m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(w + center.x() + (m_bottomRight?0:mid + m_radius), h + center.y() + m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(-w + center.x() + (m_bottomLeft?0:-mid - m_radius), h + center.y() + m_radius + mid, r, g, b, alpha);

        //Outer
        vertices[++idx].set(w + center.x() + (m_bottomRight?0:mid + aaoffset + m_radius), h + center.y() + m_radius + mid + aaoffset, 0, 0, 0, 0);
        vertices[++idx].set(-w + center.x() + (m_bottomLeft?0:-mid - aaoffset - m_radius), h  + center.y()+ m_radius + mid + aaoffset, 0, 0, 0, 0);

        if (m_bottomLeft)
            drawCircle(-w + center.x(), h + center.y(), float(M_PI) / 2.0f, false);

        //Outer
        vertices[++idx].set(-w + center.x() - m_radius - mid - aaoffset, -h + center.y() + (m_topLeft?0:-mid - aaoffset - m_radius), 0, 0, 0, 0);

        //Center
        vertices[++idx].set(-w + center.x() - m_radius - mid, h + center.y() + (m_bottomLeft?0:mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(-w + center.x() - m_radius - mid, -h + center.y() + (m_topLeft?0:-mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(-w + center.x() - m_radius + mid, h + center.y() + (m_bottomLeft?0:-mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(-w + center.x() - m_radius + mid, -h + center.y() + (m_topLeft?0:mid - m_radius), r, g, b, alpha);

        //Inner
        vertices[++idx].set(-w + center.x() - m_radius + mid + aaoffset, h + center.y() + (m_bottomLeft?0:-mid - aaoffset + m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(-w + center.x() - m_radius + mid + aaoffset, -h + center.y() + (m_topLeft?0:mid + aaoffset - m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
    }

    return nodeBorder;
}

QSGNode *RoundedRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node;
    QSGGeometry *geometry;
	auto idx = -1;
    const auto aaoffset = 1;
    const auto h = (height() - m_radius * 2.f) / 2.f;
    const auto w = (width() - m_radius * 2.f) / 2.f;
    const uchar r = m_fillColor.red();
    const uchar g = m_fillColor.green();
    const uchar b = m_fillColor.blue();
    const uchar alpha = m_fillColor.alpha();
    const auto nCorner = getNumberRoundedCorner();
    const auto aa = (m_borderWidth < 1) && antialiasing();
    const auto a = 0.5f * float(M_PI) / m_nbSegments;
    const QPointF center(w + m_radius, h + m_radius);
    m_nbSegments += (m_nbSegments % 2 == 0)?0:1;
    const int nbVertice = (aa?28:20) + nCorner * (aa ? (m_nbSegments * m_nbSegments % 2 == 0 ? (4*m_nbSegments + 1) : (4*(m_nbSegments-1)+7)):(2 * m_nbSegments + 1)) -1; /* 20 = 4 * 5 (nbVertice * nbRects) with aa 28 = 4 * 5 + 2 * 4 (nbVertice * nbRects + nbVerticeAA * (nbRects - 1)) */

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertice);
        geometry->setDrawingMode(aa?QSGGeometry::DrawTriangleStrip:QSGGeometry::DrawLineStrip);
	    const auto material = new QSGVertexColorMaterial;
        geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(nbVertice);
    }

	auto vertices = geometry->vertexDataAsColoredPoint2D();

	const auto drawCircle = [&](qreal cx, qreal cy, float offset) {
        for (uint i = 0; i < m_nbSegments; i++)
        {
            if (aa)
            {
                if (i % 2 == 0)
                {
                    vertices[++idx].set( cx, cy, r, g, b, alpha);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i + offset), cy + (m_radius + aaoffset) * qFastSin(a * i + offset), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1) + offset), 0, 0, 0, 0);
                }
                else
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1) + offset), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1) + offset), 0, 0, 0, 0);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
                }
            }
            else
            {
                vertices[++idx].set( cx, cy, r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
            }
        }
        vertices[++idx].set( cx, cy, r, g, b, alpha);
    };

    //Top
    if (m_topLeft)
        drawCircle(-w + center.x(), -h + center.y(), float(M_PI) / 2.0f * 2.0f);
    if (aa)
    {
        vertices[++idx].set( -w + center.x() + (m_topLeft ? 0 : -m_radius), - h + center.y() - m_radius - aaoffset, 0, 0, 0, 0);
        vertices[++idx].set( w + center.x() + (m_topRight ? 0 : m_radius), - h + center.y() - m_radius - aaoffset, 0, 0, 0, 0);
    }
    vertices[++idx].set( -w + center.x() + (m_topLeft ? 0 : -m_radius), - h + center.y() - m_radius, r, g, b, alpha);
    vertices[++idx].set( w + center.x() + (m_topRight ? 0 : m_radius), - h + center.y() - m_radius, r, g, b, alpha);
    vertices[++idx].set( -w + center.x() + (m_topLeft ? 0 : -m_radius), - h + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x() + (m_topRight ? 0 : m_radius), - h + center.y(), r, g, b, alpha);
    if (m_topRight)
        drawCircle(w + center.x(), -h + center.y(), float(M_PI) / 2.0f * 3.0f);

    //Right
    if (aa)
    {
        vertices[++idx].set( w + center.x() + m_radius + aaoffset, - h + center.y(), 0, 0, 0, 0);
        vertices[++idx].set( w + center.x() + m_radius + aaoffset, h + center.y(), 0, 0, 0, 0);
    }
    vertices[++idx].set( w + center.x() + m_radius, - h + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x() + m_radius, h + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x(), - h + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x(), h + center.y(), r, g, b, alpha);

    //Bottom
    if (m_bottomRight)
        drawCircle(w + center.x(), h + center.y(), 0);
    if (aa)
    {
        vertices[++idx].set( w + center.x() + ((m_bottomRight)?0:m_radius), h + m_radius + aaoffset + center.y(), 0, 0, 0, 0);
        vertices[++idx].set( -w + center.x() + ((m_bottomLeft)?0:-m_radius), h + m_radius + aaoffset + center.y(), 0, 0, 0, 0);
    }
    vertices[++idx].set( w + center.x() + (m_bottomRight ? 0 : m_radius), h + m_radius + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x() + (m_bottomLeft ? 0 : -m_radius), h + m_radius + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x() + (m_bottomRight ? 0 : m_radius), h + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x() + (m_bottomLeft ? 0 : -m_radius), h + center.y(), r, g, b, alpha);
    if (m_bottomLeft)
        drawCircle(-w + center.x(), h + center.y(), float(M_PI) / 2.0f);

    //Left
    if (aa)
    {
        vertices[++idx].set( -w + center.x() - m_radius - aaoffset, h + center.y(), 0, 0, 0, 0);
        vertices[++idx].set( -w + center.x() - m_radius - aaoffset, -h + center.y(), 0, 0, 0, 0);
    }
    vertices[++idx].set( -w + center.x() - m_radius, h + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x() - m_radius, -h + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x(), h + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x(), - h + center.y(), r, g, b, alpha);

    //Center
    vertices[++idx].set( w + center.x(), -h + center.y(), r, g, b, alpha);
    vertices[++idx].set( -w + center.x(), h + center.y(), r, g, b, alpha);
    vertices[++idx].set( w + center.x(), h + center.y(), r, g, b, alpha);

    if (m_borderWidth > 0)
        node->appendChildNode(createBorder());

    Q_ASSERT(idx + 1 == nbVertice);

    return node;
}
