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
			explicit LinkableBezierItem(QQuickItem *parent = nullptr);
            interfaces::ALinkable *getLinkable() const { return m_linkable; }
			virtual QPointF getCanvasPos() const = 0;
			virtual void updateLink() = 0;

			/**
			* \brief Make componentComplete Abstract
			*/
            void componentComplete() override = 0;
			virtual GenericNode *getNode() = 0;

			virtual void unlinkAll();
            virtual void asyncUnlinkAll();
			void connect(LinkableBezierItem* a);

            virtual void setIsLink(bool isLink) = 0;
            virtual void setIsHover(bool isHover) = 0;
            virtual const QColor &curveColor() const = 0;

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
            void mouseMoveEvent(QMouseEvent *event) override;
			/**
			* \brief Override mousePressEvent
			* \param event
			*/
             void mousePressEvent(QMouseEvent *event) override;
            /**
			* \brief Override mouseReleaseEvent
			* \param event
			*/
            void mouseReleaseEvent(QMouseEvent *event) override;

            virtual void afterRealease(Link *l);

			enum LinkStatus {
				Normal,
				Hover,
				Linked
            };

		protected:
            interfaces::ALinkable *m_linkable;
			LinkStatus m_status;
		};
	}
}

#endif // LINKABLEBEZIERITEM_H
