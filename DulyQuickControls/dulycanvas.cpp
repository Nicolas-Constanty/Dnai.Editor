#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>

#include "dulycanvas.h"
#include "line.h"

DulyCanvas::DulyCanvas(QQuickItem *parent)
    : QQuickItem(parent)
    , m_gridStep(15)
    , m_accentGridStep(150)
    , m_backgroundColor(Qt::transparent)
{
    setFlag(ItemHasContents, true);
//    CreateGrid();
}

void DulyCanvas::CreateGrid()
{

   auto drawGrid =
        [&](double gridStep, int lineWidth, const QColor &color)
    {

        QRectF windowRect = boundingRect();
        qInfo() << windowRect.height();
        qInfo() << windowRect.width();
        QPointF tl = mapToScene(windowRect.topLeft());
        QPointF br = mapToScene(windowRect.bottomRight());

        double left = std::floor(tl.x() / gridStep - 0.5);
        double right = std::floor(br.x() / gridStep + 1.0);
        double bottom = std::floor(tl.y() / gridStep - 0.5);
        double top = std::floor(br.y() / gridStep + 1.0);

        // vertical lines
        for (int xi = int(left); xi <= int(right); ++xi)
        {
            new Line(QPointF(xi * gridStep, bottom * gridStep), QPointF(xi * gridStep, top * gridStep), lineWidth, color, this);
        }

        // horizontal lines
        for (int yi = int(bottom); yi <= int(top); ++yi)
        {
            new Line(QPointF(left * gridStep, yi * gridStep), QPointF(right * gridStep, yi * gridStep), lineWidth, color, this);
        }
    };
    drawGrid(m_gridStep, 1, m_gridColor);

    drawGrid(m_accentGridStep, 2, m_accentGridColor);

}

DulyCanvas::~DulyCanvas()
{

}

void DulyCanvas::setAccentGridStep(int step)
{
    if (step == m_accentGridStep)
        return;
    m_accentGridStep = step;
    emit accentGridStepChanged(step);
    update();
}


void DulyCanvas::setGridStep(int step)
{
    if (step == m_gridStep)
        return;
    m_gridStep = step;
    emit gridStepChanged(step);
    update();
}

void DulyCanvas::setAccentGridColor(const QColor &color)
{
    if (color == m_accentGridColor)
        return;
    m_accentGridColor = color;
    emit accentGridColorChanged(color);
    update();
}


void DulyCanvas::setGridColor(const QColor &color)
{
    if (color == m_gridColor)
        return;
    m_gridColor = color;
    emit gridColorChanged(color);
    update();
}

void DulyCanvas::setBackgroundColor(const QColor &color)
{
    if (color == m_backgroundColor)
        return;
    m_backgroundColor = color;
    emit backgroundColorChanged(color);
    update();
}

QSGNode *DulyCanvas::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!n) {
       n = new QSGSimpleRectNode();
    }
    n->setColor(m_backgroundColor);
    n->setRect(boundingRect());
    CreateGrid();
//    n->markDirty(QSGNode::DirtyGeometry);

    return n;
}
