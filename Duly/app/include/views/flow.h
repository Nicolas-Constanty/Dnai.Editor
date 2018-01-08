#ifndef FLOW_H
#define FLOW_H

#include "flowtype.h"
#include "baselinkable.h"
#include "linkablebezieritem.h"

namespace duly_gui
{
	namespace views
	{
		class FlowBackend : public BaseLinkable
		{
		public:
            explicit FlowBackend(FlowTypeRessouce::FlowType t, QQuickItem *parent);

			/**
			* \brief return the IOType
			*/
            FlowTypeRessouce::FlowType getType() const;

			Link *connect(ALinkable* linkable, BezierCurve* curve) override;

		protected:
            FlowTypeRessouce::FlowType m_typeFlow;
		};

		class Flow : public LinkableBezierItem
		{
			Q_OBJECT
            Q_PROPERTY(FlowTypeRessouce::FlowType typeFlow READ typeFlow WRITE setTypeFlow NOTIFY typeFlowChanged)

		public:
			explicit Flow(QQuickItem *parent = nullptr);
			virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

		public:
            FlowTypeRessouce::FlowType typeFlow() const { return m_typeFlow; }

		public:
            void setTypeFlow(FlowTypeRessouce::FlowType t);
			/**
			* \brief Override componentComplete, and init some values
			*/
			virtual void componentComplete() override;

			virtual QPointF getCanvasPos() const override;

			virtual const QColor &colorLink() const override;

			/**
			* \brief Override findIo, return the IO under the point p of the Node n
			* \param n
			* \param p
			* \return Io *
			*/
			virtual LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) override;
			virtual void updateLink() override;
			virtual GenericNode *getNode() const override;

			virtual void setHover() override;
			virtual void setLink(Link *) override;

		signals:
            void typeFlowChanged(FlowTypeRessouce::FlowType t);

		private:
            FlowTypeRessouce::FlowType m_typeFlow;

		protected:
			void mousePressEvent(QMouseEvent* event) override;
			virtual void afterRealease(Link *l) override;
		};
	}
}


#endif // FLOW_H
