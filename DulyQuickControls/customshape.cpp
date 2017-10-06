#include "customshape.h"

CustomShape::CustomShape(QQuickItem * parent) : 
	QQuickItem(parent)
	, m_radius(5)
	, m_borderWidth(3)
	, m_fillColor(QColor(255, 255, 255))
	, m_borderColor(QColor(0, 255, 0))
{
}

void CustomShape::setRadius(qreal radius)
{

	if (radius == m_radius)
		return;
	m_radius = radius;
    emit radiusChanged(radius);
	update();
}

void CustomShape::setBorderWidth(qreal w)
{
	if (w == m_borderWidth)
		return;
	m_borderWidth = w;
	emit borderWidthChanged(w);
	update();
}

void CustomShape::setFillColor(const QColor &color)
{
	if (color == m_fillColor)
		return;
	m_fillColor = color;
	emit fillColorChanged(color);
	update();
}

void CustomShape::setBorderColor(const QColor &color)
{
	if (color == m_borderColor)
		return;
	m_borderColor = color;
	emit borderColorChanged(color);
	update();
}
