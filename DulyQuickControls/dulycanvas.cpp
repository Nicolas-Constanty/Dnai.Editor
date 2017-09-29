#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>
#include <QtMath>
#include <algorithm>

#include "dulycanvas.h"
#include "line.h"

DulyCanvas::DulyCanvas(QQuickItem *parent)
    : QQuickItem(parent)
    , m_gridStep(15)
    , m_accentGridStep(150)
    , m_backgroundColor(Qt::transparent)
    , m_scaleFactor(1)
{
    setFlag(ItemHasContents, true);
//    CreateGrid();
}

void DulyCanvas::CreateGrid()
{
    m_lines.clear();
	const auto drawGrid = [&](double gridStep, int lineWidth, const QColor &color)
    {
        gridStep *= m_scaleFactor;
        lineWidth *= m_scaleFactor;
        QRectF windowRect = boundingRect();
        QPointF tl = mapToScene(windowRect.topLeft());
        QPointF br = mapToScene(windowRect.bottomRight());

        double left = qFloor(tl.x() / gridStep - 0.5);
        double right = qFloor(br.x() / gridStep + 1.0);
        double bottom = qFloor(tl.y() / gridStep - 0.5);
        double top = qFloor(br.y() / gridStep + 1.0);

        // vertical lines
        for (int xi = int(left); xi <= int(right); ++xi)
        {
            m_lines.push_back(Line::CreateRawLine(QPointF(xi * gridStep, bottom * gridStep), QPointF(xi * gridStep, top * gridStep), lineWidth, color));
        }

        // horizontal lines
        for (int yi = int(bottom); yi <= int(top); ++yi)
        {
            m_lines.push_back(Line::CreateRawLine(QPointF(left * gridStep, yi * gridStep), QPointF(right * gridStep, yi * gridStep), lineWidth, color));
        }
    };
    drawGrid(m_gridStep, 1, m_gridColor);

    drawGrid(m_accentGridStep, 2, m_accentGridColor);

}

DulyCanvas::~DulyCanvas()
{
	const auto deleteNodes = [&](QSGGeometryNode *o) { delete o; return true; };
    m_lines.remove_if(deleteNodes);
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

void DulyCanvas::setScaleFactor(double scale)
{
    if (scale == m_scaleFactor)
        return;
    m_scaleFactor = scale;
    emit scaleFactorChanged(scale);
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
    if (m_lines.size() > 0 && oldNode)
    {
        n->removeAllChildNodes();
	    const auto deleteNodes = [&](QSGGeometryNode *o) { delete o; return true; };
        m_lines.remove_if(deleteNodes);
    }
    CreateGrid();
	const auto setParent = [&](QSGGeometryNode *o) { n->appendChildNode(o); };
    std::for_each(m_lines.begin(), m_lines.end(), setParent);

    return n;
}
