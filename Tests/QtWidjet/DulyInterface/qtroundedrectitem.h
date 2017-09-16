#ifndef QTROUNDEDRECTITEM_H
#define QTROUNDEDRECTITEM_H
#include <QGraphicsEllipseItem>


class QtRoundedRectItem : public QGraphicsRectItem
{
public:
	explicit QtRoundedRectItem(QGraphicsItem *parent = Q_NULLPTR);

	explicit QtRoundedRectItem(const QRectF &rect, const double radius_x, const double radius_y, QGraphicsItem *parent = Q_NULLPTR);

	explicit QtRoundedRectItem(qreal x, qreal y, qreal w, qreal h, const double radius_x, const double radius_y, QGraphicsItem *parent = Q_NULLPTR);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	///Get the rounded rect corner x radius
	double getRadiusX() const { return m_radius_x; }

	///Get the rounded rect corner y radius
	double getRadiusY() const { return m_radius_y; }

	///Set the rounded rect corner x radius
	void setRadiusX(const double radius_x) { m_radius_x = radius_x; }

	///Set the rounded rect corner y radius
	void setRadiusY(const double radius_y) { m_radius_y = radius_y; }

	///Set the rounded rect
	void setRoundedRect(const QRectF rect, const double radius_x, const double radius_y);

private:

	///The rounded rect corner x radius
	double m_radius_x;

	///The rounded rect corner y radius
	double m_radius_y;
};

#endif // QTROUNDEDRECTITEM_H