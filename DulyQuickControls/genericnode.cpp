#include <QtQuick/qsgflatcolormaterial.h>


#include "genericnode.h"

GenericNode::GenericNode(QQuickItem *parent) : QQuickItem(parent), m_radius(10)
{
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
