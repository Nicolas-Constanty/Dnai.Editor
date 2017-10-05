#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "beziercurve.h"

BezierCurve::BezierCurve(QQuickItem *parent)
    : QQuickItem(parent)
    , m_p1(0, 0)
    , m_p2(0.5, 0)
    , m_p3(0.5, 1)
    , m_p4(1, 1)
    , m_lineWidth(1)
    , m_segmentCount(32)
    , m_dotted(true)
    , m_fillColor(QColor(255, 0, 0))
    , m_scale(1.0, 1.0)
    , m_lastScale(1,1)
{
    setFlag(ItemHasContents, true);
    setAntialiasing(true);
    m_fillColor = m_settings.value("FilledConnectionColor/colorSelected").value<QColor>();
    m_dottedColor = m_settings.value("DottedConnectionColor/colorSelected").value<QColor>();
}

BezierCurve::~BezierCurve()
{
}

void BezierCurve::setP1(const QPointF &p)
{
    if (p == m_p1)
        return;

    m_p1 = p;
    emit p1Changed(p);
    update();
}

void BezierCurve::setP2(const QPointF &p)
{
    if (p == m_p2)
        return;

    m_p2 = p;
    emit p2Changed(p);
    update();
}

void BezierCurve::setP3(const QPointF &p)
{
    if (p == m_p3)
        return;

    m_p3 = p;
    emit p3Changed(p);
    update();
}

void BezierCurve::setP4(const QPointF &p)
{
    if (p == m_p4)
        return;
    if (p.x() < 0)
        m_scale.setX(-1);
    else
        m_scale.setX(1);
    if (p.y() < 0)
        m_scale.setY(-1);
    else
        m_scale.setY(1);

    setWidth(qAbs(p.x()) + ((p.x() < 0)?1:-1) * position().x());
    setHeight(qAbs(p.y()) + ((p.y() < 0)?1:-1) * position().y());

    emit p4Changed(p);
    update();
}

void BezierCurve::setLineWidth(uint w)
{
    if (w == m_lineWidth)
        return;
    m_lineWidth = w;
    emit lineWidthChanged(w);
    update();
}

void BezierCurve::setSegmentCount(uint count)
{
    if (m_segmentCount == count)
        return;

    m_segmentCount = count;
    emit segmentCountChanged(count);
    update();
}

void BezierCurve::setDotted(bool dotted)
{
    if (dotted == m_dotted)
        return;
    m_dotted = dotted;
    emit dottedChanged(dotted);
    update();
}


void BezierCurve::setFillColor(const QColor &color)
{
    if (color == m_fillColor)
        return;
    m_fillColor = color;
    emit fillColorChanged(color);
    update();
}

void BezierCurve::setDottedColor(const QColor &color)
{
    if (color == m_dottedColor)
        return;
    m_dottedColor = color;
    emit dottedColorChanged(color);
    update();
}

QSGNode *BezierCurve::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    QSGGeometryNode *node;
    QSGGeometry *geometry;
    const auto aa = antialiasing();
    const auto radius = float(m_lineWidth) / 2.f;

    const char r = m_dotted?m_dottedColor.red():m_fillColor.red();
    const char g = m_dotted?m_dottedColor.green():m_fillColor.green();
    const char b = m_dotted?m_dottedColor.blue():m_fillColor.blue();
    const char alpha = m_dotted?m_dottedColor.alpha():m_fillColor.alpha();

    const char r1 = 0;
    const char g1 = 0;
    const char b1 = 0;
    const char alpha1 = 0;
    const auto aaoffset = 1.f;
    const auto pi2 = float(M_PI) / 2.f;
    const auto raa = radius + aaoffset;

    if (m_segmentCount != 0 && m_segmentCount % 2 != 0)
        ++m_segmentCount;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), ( aa ? m_segmentCount * 7.5 : m_segmentCount ));
        geometry->setLineWidth(1);
        geometry->setDrawingMode(aa?QSGGeometry::DrawTriangleStrip:QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGVertexColorMaterial *material = new QSGVertexColorMaterial;
        material->setFlag(QSGMaterial::Blending);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(( aa ? m_segmentCount * 7.5 : m_segmentCount ));
    }
	auto matrix = data->transformNode->matrix();
    matrix.scale((m_lastScale.x() != m_scale.x())?-1:1, (m_lastScale.y() != m_scale.y())?-1:1);
    data->transformNode->setMatrix(matrix);
    m_lastScale = m_scale;

	const auto bounds = boundingRect();
	const auto vertices = geometry->vertexDataAsColoredPoint2D();
	auto idx = -1;
    for (uint i = 0; i <  m_segmentCount - (aa?1:0); i++)
    {
        if (!aa)
        {
            const auto t = i / qreal(m_segmentCount - 1);
            const auto invt = 1 - t;

	        const auto pos = invt * invt * invt * m_p1
                        + 3 * invt * invt * t * m_p2
                        + 3 * invt * t * t * m_p3
                        + t * t * t * m_p4;

            const auto x = bounds.x() + pos.x() * bounds.width();
            const auto y = bounds.y() + pos.y() * bounds.height();
            vertices[i].set(x, y, r, g, b, alpha);
        }
        else
        {
            const auto t = i / qreal(m_segmentCount - 1);
            const auto invt = 1 - t;

	        const auto pos = invt * invt * invt * m_p1
                        + 3 * invt * invt * t * m_p2
                        + 3 * invt * t * t * m_p3
                        + t * t * t * m_p4;

            const auto x = bounds.x() + pos.x() * bounds.width();
            const auto y = bounds.y() + pos.y() * bounds.height();

            const auto t1 = (i + 1) / qreal(m_segmentCount - 1);
            const auto invt1 = 1 - t1;

	        const auto pos1 = invt1 * invt1 * invt1 * m_p1
                        + 3 * invt1 * invt1 * t1 * m_p2
                        + 3 * invt1 * t1 * t1 * m_p3
                        + t1 * t1 * t1 * m_p4;

            const auto x1 = bounds.x() + pos1.x() * bounds.width();
            const auto y1= bounds.y() + pos1.y() * bounds.height();

            const auto deltaX = x1 - x;
            const auto deltaY = y1 - y;

            const auto a = qAtan2(deltaY, deltaX);
            const auto aUp = a + pi2;
            const auto aDown = a - pi2;

            const auto xUp = radius * qFastCos(aUp);
            const auto xUpaa = raa * qFastCos(aUp);
            const auto xDown = radius * qFastCos(aDown);
            const auto xDownaa = raa * qFastCos(aDown);

            const auto yUp = radius * qFastSin(aUp);
            const auto yUpaa = raa * qFastSin(aUp);
            const auto yDown = radius * qFastSin(aDown);
            const auto yDownaa = raa * qFastSin(aDown);

            if (i % 2 == 0)
            {
                vertices[++idx].set(x + xUpaa, y + yUpaa, r1, g1, b1, alpha1);
                vertices[++idx].set(x1 + xUpaa, y1 + yUpaa, r1, g1, b1, alpha1);

                vertices[++idx].set(x + xUp, y + yUp, r, g, b, alpha);
                vertices[++idx].set(x1 + xUp, y1 + yUp, r, g, b, alpha);

                vertices[++idx].set(x + xDown, y + yDown, r, g, b, alpha);
                vertices[++idx].set(x1 + xDown, y1 + yDown, r, g, b, alpha);

                vertices[++idx].set(x + xDownaa, y + yDownaa, r1, g1, b1, alpha1);
                vertices[++idx].set(x1 + xDownaa, y1 + yDownaa, r1, g1, b1, alpha1);
            }
            else if (!m_dotted)
            {
                vertices[++idx].set(x1 + xDownaa, y1 + yDownaa, r1, g1, b1, alpha1);

                vertices[++idx].set(x + xDown, y + yDown, r, g, b, alpha);
                vertices[++idx].set(x1 + xDown, y1 + yDown, r, g, b, alpha);

                vertices[++idx].set(x + xUp, y + yUp, r, g, b, alpha);
                vertices[++idx].set(x1 + xUp, y1 + yUp, r, g, b, alpha);

                vertices[++idx].set(x + xUpaa, y + yUpaa, r1, g1, b1, alpha1);
                vertices[++idx].set(x1 + xUpaa, y1 + yUpaa, r1, g1, b1, alpha1);
            }
        }

    }

    return node;
}
