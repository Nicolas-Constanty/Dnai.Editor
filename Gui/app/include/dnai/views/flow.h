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

            Link *asyncConnect(ALinkable* linkable) override;

		protected:
            enums::FlowTypeRessouce::FlowType m_typeFlow;
		};

		class Flow : public LinkableBezierItem
		{
			Q_OBJECT
            Q_PROPERTY(dnai::enums::FlowTypeRessouce::FlowType typeFlow READ typeFlow WRITE setTypeFlow NOTIFY typeFlowChanged)
            Q_PROPERTY(bool isLink READ isLink WRITE setIsLink NOTIFY isLinkChanged)
            Q_PROPERTY(bool isHover READ isHover WRITE setIsHover NOTIFY isHoverChanged)
            Q_PROPERTY(QColor curveColor READ curveColor WRITE setCurveColor NOTIFY curveColorChanged)

		public:
			explicit Flow(QQuickItem *parent = nullptr);
            QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

		public:
            enums::FlowTypeRessouce::FlowType typeFlow() const { return m_typeFlow; }

		public:
            void setTypeFlow(enums::FlowTypeRessouce::FlowType t);
			/**
			* \brief Override componentComplete, and init some values
			*/
            void componentComplete() override;

			/**
			* \brief Override findIo, return the IO under the point p of the Node n
			* \param n
			* \param p
			* \return Io *
			*/
            LinkableBezierItem *findLinkableBezierItem(GenericNode *n, const QPointF &p) override;
            void updateLink() override;
            GenericNode *getNode() override;

            QPointF getCanvasPos() const override;
			void unlinkAll() override;
            void asyncUnlinkAll() override;

            bool isLink() const;

            bool isHover() const;

            const QColor &curveColor() const override;

        public slots:
            void setIsLink(bool isLink) override;

            void setIsHover(bool isHover) override;

            void setCurveColor(const QColor &colorCurve);

        signals:
            void typeFlowChanged(enums::FlowTypeRessouce::FlowType t);
			void linked(int outindex, const QVariant &instructionModel);
			void unlinked(int outindex, const QVariant &instructionModel);

            void isLinkChanged(bool isLink);

            void isHoverChanged(bool isHover);

            void curveColorChanged(const QColor &colorCurve);

        private:
            enums::FlowTypeRessouce::FlowType m_typeFlow;
			GenericNode *m_genericNode;

            bool m_isLink;

            bool m_isHover;

            QColor m_colorCurve;

        protected:
			void mousePressEvent(QMouseEvent* event) override;
            void afterRealease(Link *l) override;
		};
	}
}


#endif // FLOW_H
