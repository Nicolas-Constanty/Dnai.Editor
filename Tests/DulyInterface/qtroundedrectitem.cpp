#include "qtroundedrectitem.h"

#include <QGraphicsScene>
#include <QPainter>

QtRoundedRectItem::QtRoundedRectItem(QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	this->setFlags(
		QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable);

}

QtRoundedRectItem::QtRoundedRectItem(const QRectF& rect, const double radius_x, const double radius_y,  QGraphicsItem* parent) 
: QGraphicsRectItem(rect, parent) , m_radius_x(radius_x), m_radius_y(radius_y)
{
	this->setFlags(
		QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable);
}

QtRoundedRectItem::QtRoundedRectItem(qreal x, qreal y, qreal w, qreal h, const double radius_x, const double radius_y, QGraphicsItem* parent)
: QGraphicsRectItem(x,y,w,h,parent), m_radius_x(radius_x), m_radius_y(radius_y)
{
	this->setFlags(
		QGraphicsItem::ItemIsFocusable
		| QGraphicsItem::ItemIsMovable
		| QGraphicsItem::ItemIsSelectable);
}

void QtRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (this->isSelected())
	{
		QPen pen;
		pen.setStyle(Qt::DashLine);
		painter->setPen(pen);
	}
	painter->setBrush(QBrush(Qt::gray));
	painter->drawRoundedRect(this->rect(), m_radius_x, m_radius_y);
}

void QtRoundedRectItem::setRoundedRect(const QRectF rect, const double radius_x, const double radius_y)
{
	this->setRect(rect);
	this->setRadiusX(radius_x);
	this->setRadiusY(radius_y);
}
