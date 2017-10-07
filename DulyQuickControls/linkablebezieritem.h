#ifndef LINKABLEBEZIERITEM_H
#define LINKABLEBEZIERITEM_H

#include "customshape.h"
#include "beziercurve.h"
#include "ilinkable.h"


class GenericNode;

class LinkableBezierItem  : public CustomShape
{
public:
    LinkableBezierItem(QQuickItem *parent = nullptr);
    ALinkable *getLinkable() const { return m_linkable; }
    virtual QPointF getCanvasPos() const = 0;
	virtual void updateLink() = 0;

	/**
	* \brief Make componentComplete Abstract
	*/
	virtual void componentComplete() override = 0;
    virtual GenericNode *getNode() const = 0;

    virtual const QColor &colorLink() const;

protected:
	BezierCurve *m_currentCurve;

protected:
    /**
	* \brief return the IO under the point p of the Node n
	* \param n
	* \param p
	* \return Io *
	*/
	virtual LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) = 0;

	/**
	* \brief Override mouseMoveEvent
	* \param event
	*/
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	/**
	* \brief Override mousePressEvent
	* \param event
	*/
	virtual void mousePressEvent(QMouseEvent *event) override;
	/**
	* \brief Override mouseReleaseEvent
	* \param event
	*/
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected:
	ALinkable *m_linkable;

};

#endif // LINKABLEBEZIERITEM_H
