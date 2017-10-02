#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "roundedrectangle.h"
#include "qsgdefaultroundedrectangle.h"

RoundedRectangle::RoundedRectangle(QQuickItem *parent) :
    QQuickItem(parent),
    m_roundedSegments(5),
    m_topLeft(true),
    m_topRight(true),
    m_bottomLeft(true),
    m_bottomRight(true),
    m_borderColor(QColor(0,0,0)),
    m_border(0)
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

void RoundedRectangle::setRadius(qreal radius)
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

void RoundedRectangle::setBorder(qreal b)
{
    if (m_border == b)
        return;
    m_border = b;
    emit borderChanged(b);
    update();
}

void RoundedRectangle::setBorderColor(const QColor &color)
{
    if (color == m_borderColor)
        return;
    m_borderColor = color;
    emit borderColorChanged(color);
    update();
}

void RoundedRectangle::setFillColor(const QColor &color)
{
    if (color == m_fillColor)
        return;
    m_fillColor = color;
    emit fillColorChanged(color);
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

QSGGeometryNode *RoundedRectangle::CreateBorder() const
{
    int idx = -1;
    const qreal h = (height() / 2.f - m_radius) / 2.f;
    const qreal w = (width() + m_radius * 2.f) / 2.f;
    const float a = 0.5f * float(M_PI) / m_roundedSegments;
    const bool aa = antialiasing();
    const int nCorner = GetNumberRoundedCorner();
    const uint aaoffset = 1;
    const uchar r = m_borderColor.red();
    const uchar g = m_borderColor.green();
    const uchar b = m_borderColor.blue();
    const uchar alpha = m_borderColor.alpha();
    const uint nbVertice = (aa ? (m_roundedSegments % 2 == 0 ? (7.5 * m_roundedSegments) : (7.5 * (m_roundedSegments-1)+8) ) : m_roundedSegments) * nCorner + (aa?7*4+(m_topLeft?0:1):8) + (aa?0:-nCorner);

    QSGGeometryNode *bufferBorder = new QSGGeometryNode;
    QSGVertexColorMaterial *materialBorder = new QSGVertexColorMaterial;
    QSGGeometry *bufferBorderGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertice);
    if (!aa)
        bufferBorderGeometry->setLineWidth(m_border);
    bufferBorderGeometry->setDrawingMode(aa ? QSGGeometry::DrawTriangleStrip : QSGGeometry::DrawLineStrip);
    bufferBorder->setGeometry(bufferBorderGeometry);
    bufferBorder->setFlag(QSGNode::OwnsGeometry, aa);
    materialBorder->setFlag(QSGMaterial::Blending);

    bufferBorder->setMaterial(materialBorder);

    QSGGeometry::ColoredPoint2D *vertices = bufferBorderGeometry->vertexDataAsColoredPoint2D();
    if (!aa)
    {
        auto drawCircle = [&](qreal cx, qreal cy, float offset)
        {
            for (int i = 0; i < m_roundedSegments; i++)
                vertices[++idx].set( cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
        };
        if (m_topLeft)
            drawCircle(-w, -h, float(M_PI));
        else
            vertices[++idx].set(-w -m_radius, -h - m_radius, r, g, b, alpha);
        vertices[++idx].set(w, -h - m_radius, r, g, b, alpha);
        if (m_topRight)
            drawCircle(w, -h, (float(M_PI) / 2.f) * 3.f);
        else
            vertices[++idx].set(w + m_radius, -h -m_radius, r, g, b, alpha);

        vertices[++idx].set(w + m_radius, h, r, g, b, alpha);
        if (m_bottomRight)
            drawCircle(w, h, 0);
        else
            vertices[++idx].set(w + m_radius, h + m_radius, r, g, b, alpha);
        vertices[++idx].set(-w, h + m_radius, r, g, b, alpha);
        if (m_bottomLeft)
            drawCircle(-w, h, float(M_PI) / 2.0f);
        else
            vertices[++idx].set(-w - m_radius, h + m_radius, r, g, b, alpha);
        vertices[++idx].set(-w -m_radius, -h + ((m_topLeft)?0:- m_radius), r, g, b, alpha);
    }
    else
    {
        const qreal mid = m_border / 2.f;
        auto drawCircle = [&](qreal cx, qreal cy, float offset, bool dir = true)
        {
            for (int i = 0; i < m_roundedSegments; i++)
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
            drawCircle(-w, -h, float(M_PI));
        else
            vertices[++idx].set(-w + mid + aaoffset - m_radius, -h - m_radius + mid + aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(w + (m_topRight?0:-mid - aaoffset + m_radius), -h - m_radius + mid + aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        //Center
        vertices[++idx].set(-w + (m_topLeft?0:mid - m_radius), -h - m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(w + (m_topRight?0:mid  + m_radius), -h - m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(-w + (m_topLeft?0:-mid - m_radius), -h - m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(w + (m_topRight?0:mid + m_radius), -h - m_radius - mid, r, g, b, alpha);

        //Outer
        vertices[++idx].set(-w + (m_topLeft?0:-mid - aaoffset - m_radius), -h - m_radius - mid - aaoffset, 0, 0, 0, 0);
        vertices[++idx].set(w + (m_topRight?0:mid + aaoffset + m_radius), -h - m_radius - mid - aaoffset, 0, 0, 0, 0);

        if (m_topRight)
            drawCircle(w, -h, (float(M_PI) / 2.f) * 3.f, false);

        //Outer
        vertices[++idx].set(w + m_radius + mid + aaoffset, h + (m_bottomRight?0:mid + aaoffset + m_radius), 0, 0, 0, 0);

        //Center
        vertices[++idx].set(w + m_radius + mid, -h + (m_topRight?0:-mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(w + m_radius + mid, h + (m_bottomRight?0:mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(w + m_radius - mid, -h + (m_topRight?0:mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(w + m_radius - mid, h + (m_bottomRight?0:-mid + m_radius), r, g, b, alpha);

        //Inner
        vertices[++idx].set(w + m_radius - mid - aaoffset, -h + (m_topRight?0:mid + aaoffset - m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(w + m_radius - mid - aaoffset, h + (m_bottomRight?0:-mid - aaoffset + m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        if (m_bottomRight)
            drawCircle(w, h, 0);

        //Inner
        vertices[++idx].set(-w + (m_bottomLeft?0:mid + aaoffset - m_radius), h + m_radius - mid - aaoffset, m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());

        //Center
        vertices[++idx].set(w + (m_bottomRight?0:-mid + m_radius), h + m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(-w + (m_bottomLeft?0:mid - m_radius), h + m_radius - mid, r, g, b, alpha);
        vertices[++idx].set(w + (m_bottomRight?0:mid + m_radius), h + m_radius + mid, r, g, b, alpha);
        vertices[++idx].set(-w + (m_bottomLeft?0:-mid - m_radius), h + m_radius + mid, r, g, b, alpha);

        //Outer
        vertices[++idx].set(w + (m_bottomRight?0:mid + aaoffset + m_radius), h + m_radius + mid + aaoffset, 0, 0, 0, 0);
        vertices[++idx].set(-w + (m_bottomLeft?0:-mid - aaoffset - m_radius), h + m_radius + mid + aaoffset, 0, 0, 0, 0);

        if (m_bottomLeft)
            drawCircle(-w, h, float(M_PI) / 2.0f, false);

        //Outer
        vertices[++idx].set(-w - m_radius - mid - aaoffset, -h + (m_topLeft?0:-mid - aaoffset - m_radius), 0, 0, 0, 0);

        //Center
        vertices[++idx].set(-w - m_radius - mid, h + (m_bottomLeft?0:mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(-w - m_radius - mid, -h + (m_topLeft?0:-mid - m_radius), r, g, b, alpha);
        vertices[++idx].set(-w - m_radius + mid, h + (m_bottomLeft?0:-mid + m_radius), r, g, b, alpha);
        vertices[++idx].set(-w - m_radius + mid, -h + (m_topLeft?0:mid - m_radius), r, g, b, alpha);

        //Inner
        vertices[++idx].set(-w - m_radius + mid + aaoffset, h + (m_bottomLeft?0:-mid - aaoffset + m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
        vertices[++idx].set(-w - m_radius + mid + aaoffset, -h + (m_topLeft?0:mid + aaoffset - m_radius), m_fillColor.red(), m_fillColor.green(), m_fillColor.blue(), m_fillColor.alpha());
    }

    return bufferBorder;
}

QSGNode *RoundedRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    int idx = -1;
    const uint aaoffset = 1;
    const qreal h = (height() / 2.f - m_radius) / 2.f;
    const qreal w = (width() + m_radius * 2.f) / 2.f;
    const uchar r = m_fillColor.red();
    const uchar g = m_fillColor.green();
    const uchar b = m_fillColor.blue();
    const uchar alpha = m_fillColor.alpha();
    const int nCorner = GetNumberRoundedCorner();
    const bool aa = (m_border < 1) && antialiasing();
    const float a = 0.5f * float(M_PI) / m_roundedSegments;
    m_roundedSegments += (m_roundedSegments % 2 == 0)?0:1;
    const int nbVertice = (aa?28:20) + nCorner * (aa ? (m_roundedSegments * m_roundedSegments % 2 == 0 ? (4*m_roundedSegments + 1) : (4*(m_roundedSegments-1)+7)):(2 * m_roundedSegments + 1)) -1; /* 20 = 4 * 5 (nbVertice * nbRects) with aa 28 = 4 * 5 + 2 * 4 (nbVertice * nbRects + nbVerticeAA * (nbRects - 1)) */

    QSGGeometryNode *buffer = new QSGGeometryNode;
    QSGGeometry *bufferGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertice);
    QSGVertexColorMaterial *material = new QSGVertexColorMaterial;

    bufferGeometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
    buffer->setGeometry(bufferGeometry);
    buffer->setFlag(QSGNode::OwnsGeometry);
    buffer->setMaterial(material);
    buffer->setFlag(QSGNode::OwnsMaterial);

    QSGGeometry::ColoredPoint2D *vertices = bufferGeometry->vertexDataAsColoredPoint2D();

    auto drawCircle = [&](qreal cx, qreal cy, float offset) {
        for (int i = 0; i < m_roundedSegments; i++)
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
        drawCircle(-w, -h, float(M_PI) / 2.0f * 2.0f);
    if (aa)
    {
        vertices[++idx].set( -w + (m_topLeft ? 0 : -m_radius), - h - m_radius - aaoffset, 0, 0, 0, 0);
        vertices[++idx].set( w + (m_topRight ? 0 : m_radius), - h - m_radius - aaoffset, 0, 0, 0, 0);
    }
    vertices[++idx].set( -w + (m_topLeft ? 0 : -m_radius), - h - m_radius, r, g, b, alpha);
    vertices[++idx].set( w + (m_topRight ? 0 : m_radius), - h - m_radius, r, g, b, alpha);
    vertices[++idx].set( -w + (m_topLeft ? 0 : -m_radius), - h, r, g, b, alpha);
    vertices[++idx].set( w + (m_topRight ? 0 : m_radius), - h, r, g, b, alpha);
    if (m_topRight)
        drawCircle(w, -h, float(M_PI) / 2.0f * 3.0f);

    //Right
    if (aa)
    {
        vertices[++idx].set( w + m_radius + aaoffset, - h, 0, 0, 0, 0);
        vertices[++idx].set( w + m_radius + aaoffset, h, 0, 0, 0, 0);
    }
    vertices[++idx].set( w + m_radius, - h, r, g, b, alpha);
    vertices[++idx].set( w + m_radius, h, r, g, b, alpha);
    vertices[++idx].set( w, - h, r, g, b, alpha);
    vertices[++idx].set( w, h, r, g, b, alpha);

    //Bottom
    if (m_bottomRight)
        drawCircle(w, h, 0);
    if (aa)
    {
        vertices[++idx].set( w + ((m_bottomRight)?0:m_radius), h + m_radius + aaoffset, 0, 0, 0, 0);
        vertices[++idx].set( -w + ((m_bottomLeft)?0:-m_radius), h + m_radius + aaoffset, 0, 0, 0, 0);
    }
    vertices[++idx].set( w + (m_bottomRight ? 0 : m_radius), h + m_radius, r, g, b, alpha);
    vertices[++idx].set( -w + (m_bottomLeft ? 0 : -m_radius), h + m_radius, r, g, b, alpha);
    vertices[++idx].set( w + (m_bottomRight ? 0 : m_radius), h, r, g, b, alpha);
    vertices[++idx].set( -w + (m_bottomLeft ? 0 : -m_radius), h, r, g, b, alpha);
    if (m_bottomLeft)
        drawCircle(-w, h, float(M_PI) / 2.0f);

    //Left
    if (aa)
    {
        vertices[++idx].set( -w - m_radius - aaoffset, h, 0, 0, 0, 0);
        vertices[++idx].set( -w - m_radius - aaoffset, -h, 0, 0, 0, 0);
    }
    vertices[++idx].set( -w - m_radius, h, r, g, b, alpha);
    vertices[++idx].set( -w - m_radius, -h, r, g, b, alpha);
    vertices[++idx].set( -w, h, r, g, b, alpha);
    vertices[++idx].set( -w, - h, r, g, b, alpha);

    //Center
    vertices[++idx].set( w, -h, r, g, b, alpha);
    vertices[++idx].set( -w, h, r, g, b, alpha);
    vertices[++idx].set( w, h, r, g, b, alpha);

    if (m_border > 0)
        buffer->appendChildNode(CreateBorder());

    Q_ASSERT(idx + 1 == nbVertice);

    return buffer;
}
