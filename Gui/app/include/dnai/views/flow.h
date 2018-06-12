#ifndef FLOW_H
#define FLOW_H

#include "linkablebezieritem.h"
#include "dnai/baselinkable.h"
#include "dnai/enums/flowtype.h"
#include "dnai/models/instruction.h"

namespace dnai
{
	namespace views
	{
		class FlowBackend : public BaseLinkable
		{
		public:
            explicit FlowBackend(enums::FlowTypeRessouce::FlowType t, QQuickItem *parent);

			/**
			* \brief return the IOType
			*/
            enums::FlowTypeRessouce::FlowType getType() const;

			Link *connect(ALinkable* linkable, BezierCurve* curve) override;

		protected:
            enums::FlowTypeRessouce::FlowType m_typeFlow;
		};

		class Flow : public LinkableBezierItem
		{
			Q_OBJECT
            Q_PROPERTY(dnai::enums::FlowTypeRessouce::FlowType typeFlow READ typeFlow WRITE setTypeFlow NOTIFY typeFlowChanged)

		public:
			explicit Flow(QQuickItem *parent = nullptr);
			virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

		public:
            enums::FlowTypeRessouce::FlowType typeFlow() const { return m_typeFlow; }

		public:
            void setTypeFlow(enums::FlowTypeRessouce::FlowType t);
			/**
			* \brief Override componentComplete, and init some values
			*/
			virtual void componentComplete() override;

			virtual const QColor &colorLink() const override;

			/**
			* \brief Override findIo, return the IO under the point p of the Node n
			* \param n
			* \param p
			* \return Io *
			*/
			virtual LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) override;
			virtual void updateLink() override;
            virtual GenericNode *getNode() override;

			virtual void setHover() override;
			virtual void setLink(Link *) override;

            QPointF getCanvasPos() const override;
			void unlinkAll() override;

        signals:
            void typeFlowChanged(enums::FlowTypeRessouce::FlowType t);
			void linked(int outindex, const QVariant &instructionModel);
			void unlinked(int outindex, const QVariant &instructionModel);

		private:
            enums::FlowTypeRessouce::FlowType m_typeFlow;
			GenericNode *m_genericNode;

		protected:
			void mousePressEvent(QMouseEvent* event) override;
			virtual void afterRealease(Link *l) override;
		};
	}
}


#endif // FLOW_H
