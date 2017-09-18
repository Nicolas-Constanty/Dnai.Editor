#include "line.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

Line::Line(QQuickItem *parent)
    : QQuickItem(parent)
    , m_p1(0, 0)
    , m_p2(1, 0)
    , m_lineWidth(2)
    , m_lineColor(QColor(255, 0, 0))
{
    setFlag(ItemHasContents, true);
    setWidth(qFabs(m_p2.x() - m_p1.x()));
    setWidth(qFabs(m_p2.y() - m_p1.y()));
}

Line::Line(const QPointF &p1, const QPointF &p2, QQuickItem *parent) : QQuickItem(parent)
  , m_p1(p1)
  , m_p2(p2)
  , m_lineWidth(2)
  , m_lineColor(QColor(255, 0, 0))
{
    setFlag(ItemHasContents, true);
    setWidth(qFabs(m_p2.x() - m_p1.x()));
    setWidth(qFabs(m_p2.y() - m_p1.y()));
}

Line::Line(const QPointF &p1, const QPointF &p2, int lineWidth, QQuickItem *parent) : QQuickItem(parent)
  , m_p1(p1)
  , m_p2(p2)
  , m_lineWidth(lineWidth)
  , m_lineColor(QColor(255, 0, 0))
{
    setFlag(ItemHasContents, true);
    setWidth(qFabs(m_p2.x() - m_p1.x()));
    setWidth(qFabs(m_p2.y() - m_p1.y()));
}

Line::Line(const QPointF &p1, const QPointF &p2, int lineWidth, const QColor &color, QQuickItem *parent) : QQuickItem(parent)
  , m_p1(p1)
  , m_p2(p2)
  , m_lineWidth(lineWidth)
  , m_lineColor(color)
{
    setFlag(ItemHasContents, true);
    setWidth(qFabs(m_p2.x() - m_p1.x()));
    setWidth(qFabs(m_p2.y() - m_p1.y()));
}

Line::~Line()
{
}

void Line::setP1(const QPointF &p)
{
    if (p == m_p1)
        return;

    m_p1 = p;
    emit p1Changed(p);
    update();
}

void Line::setP2(const QPointF &p)
{
    if (p == m_p2)
        return;

    m_p2 = p;
    emit p2Changed(p);
    update();
}

void Line::setLineWidth(int lw)
{
    if (lw == m_lineWidth)
        return;

    m_lineWidth = lw;
    emit lineWidthChanged(lw);
    update();
}

void Line::setLineColor(const QColor &color)
{
    if (color == m_lineColor)
        return;

    m_lineColor = color;
    emit lineColorChanged(color);
    update();
}

QSGNode *Line::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    setWidth(qFabs(m_p2.x() - m_p1.x()));
    setHeight(qFabs(m_p2.y() - m_p1.y()));

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setLineWidth(m_lineWidth);
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_lineColor);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(2);
    }
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    vertices[0].set(m_p1.x(), m_p1.y());
    vertices[1].set(m_p2.x(), m_p2.y());
    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
