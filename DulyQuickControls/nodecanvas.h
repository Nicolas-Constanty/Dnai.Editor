#ifndef NODECANVAS_H
#define NODECANVAS_H

#include <QGraphicsView>
#include <QWheelEvent>


class NodeCanvas : public QGraphicsView
{
public:
	NodeCanvas(QGraphicsScene *scene);

	NodeCanvas(const NodeCanvas&) = delete;
	NodeCanvas operator=(const NodeCanvas&) = delete;

protected:
    void drawBackground(QPainter* painter, const QRectF& r) override;
	void wheelEvent(QWheelEvent *event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // NODECANVAS_H
