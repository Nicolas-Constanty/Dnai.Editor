#ifndef LINKABLEBEZIERITEM_H
#define LINKABLEBEZIERITEM_H

#include "customshape.h"
#include "beziercurve.h"
#include "canvasnode.h"
#include "dnai/interfaces/ilinkable.h"

namespace dnai
{
	namespace views
	{
		class GenericNode;

		class LinkableBezierItem : public CustomShape
		{
		public:
			LinkableBezierItem(QQuickItem *parent = nullptr);
            interfaces::ALinkable *getLinkable() const { return m_linkable; }
			virtual QPointF getCanvasPos() const = 0;
			virtual void updateLink() = 0;

			/**
			* \brief Make componentComplete Abstract
			*/
			virtual void componentComplete() override = 0;
			virtual GenericNode *getNode() = 0;

			virtual const QColor &colorLink() const;

			virtual void unlinkAll();
			void connect(LinkableBezierItem* a);


		protected:
			BezierCurve *m_currentCurve;
			CanvasNode* m_canvas;

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

			virtual void afterRealease(Link *l);

			virtual void setHover();
			virtual void setNormal();
			virtual void setLink(Link *);

			enum LinkStatus {
				Normal,
				Hover,
				Linked
			};

		protected:
            interfaces::ALinkable *m_linkable;
			LinkableBezierItem *m_currentHover;
			LinkStatus m_status;

		};
	}
}

#endif // LINKABLEBEZIERITEM_H
