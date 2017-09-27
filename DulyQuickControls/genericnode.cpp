#include <QtQuick/qsgflatcolormaterial.h>
#include "nodepainter.h"


#include "genericnode.h"

GenericNode::GenericNode(QQuickItem *parent) : QNanoQuickItem(parent), m_radius(10)
{
}

QNanoQuickItemPainter* GenericNode::createItemPainter() const
{
	return new NodePainter(m_radius);
}

void GenericNode::setBackgroundColor(const QColor &color)
{
    if (color == m_backgroundColor)
        return;
    m_backgroundColor = color;
    emit backgroundColorChanged(color);
    update();
}

void GenericNode::setRadius(double radius)
{
	if (radius == m_radius)
		return;
	m_radius = radius;
	emit radiusChanged(radius);
	update();
}
