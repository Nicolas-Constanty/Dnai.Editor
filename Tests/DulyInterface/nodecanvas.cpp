#include <QtMath>
#include <QScrollBar>

#include "nodecanvas.h"
#include <QMenuBar>


NodeCanvas::NodeCanvas(QGraphicsScene* scene) : QGraphicsView(scene)
{
	setRenderHint(QPainter::Antialiasing);
}

void NodeCanvas::drawBackground(QPainter * painter, const QRectF & r)
{
	QGraphicsView::drawBackground(painter, r);

	auto drawGrid =
		[&](double gridStep)
	{
		QRect   windowRect = rect();
		QPointF tl = mapToScene(windowRect.topLeft());
		QPointF br = mapToScene(windowRect.bottomRight());

		double left = std::floor(tl.x() / gridStep - 0.5);
		double right = std::floor(br.x() / gridStep + 1.0);
		double bottom = std::floor(tl.y() / gridStep - 0.5);
		double top = std::floor(br.y() / gridStep + 1.0);

		// vertical lines
		for (int xi = int(left); xi <= int(right); ++xi)
		{
			QLineF line(xi * gridStep, bottom * gridStep,
				xi * gridStep, top * gridStep);

			painter->drawLine(line);
		}

		// horizontal lines
		for (int yi = int(bottom); yi <= int(top); ++yi)
		{
			QLineF line(left * gridStep, yi * gridStep,
				right * gridStep, yi * gridStep);
			painter->drawLine(line);
		}
	};


	QBrush bBrush = backgroundBrush();

	QPen pfine(QBrush(Qt::gray), 1.0);

	painter->setPen(pfine);
	drawGrid(15);

	QPen p(QBrush(Qt::red), 1.0);

	painter->setPen(p);
	drawGrid(150);
}

void NodeCanvas::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers() & Qt::ControlModifier) {
		// zoom
		setTransformationAnchor(AnchorUnderMouse);
		const int angle = event->angleDelta().y();
		const qreal factor = (angle > 0) ? 1.1 : .9;
		scale(factor, factor);
	}
	else {
		QGraphicsView::wheelEvent(event);
	}
}

void NodeCanvas::contextMenuEvent(QContextMenuEvent* event)
{
	//QGraphicsView::contextMenuEvent(event);
	QMenu menu(this);
	menu.addAction(QString("Command 1"));
	menu.addAction(QString("Command 2"));

	menu.exec(event->globalPos());
}
