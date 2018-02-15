#ifndef GENERICNODE_H
#define GENERICNODE_H

#include "roundedrectangle.h"
#include "flow.h"
#include "canvasnode.h"
#include "dnai/focusmanager.h"

namespace dnai
{
    namespace views {
        class GenericNode : public QQuickItem
        {
            Q_OBJECT

            Q_PROPERTY(bool flowIn READ flowIn WRITE setFlowIn NOTIFY flowInChanged)
            Q_PROPERTY(bool flowOut READ flowOut WRITE setFlowOut NOTIFY flowOutChanged)
            Q_PROPERTY(dnai::views::Flow *flowInItem READ flowInItem WRITE setFlowInItem NOTIFY flowInItemChanged)
            Q_PROPERTY(dnai::views::Flow *flowOutItem READ flowOutItem WRITE setFlowOutItem NOTIFY flowOutItemChanged)
            Q_PROPERTY(dnai::views::RoundedRectangle *header READ header WRITE setHeader NOTIFY headerChanged)
            Q_PROPERTY(dnai::views::RoundedRectangle *content READ content WRITE setContent NOTIFY contentChanged)

        public:
            explicit GenericNode(QQuickItem *parent = nullptr);
            /**
            * \brief Override updatePaintNode and draw a beautifull Node
            * \return QSGNode *
            */
            virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
            virtual void componentComplete() override;
            void resetBorderColor();
            void move(const QPointF &vec);
            const QPointF &startPos() const { return m_startPos; }
            static void resetSelected();
            //virtual bool contains(const QPointF &point) const override;

        public:
            FocusManagerIo &inputs() { return m_inputs; }
            FocusManagerIo &outputs() { return m_outputs; }

        public:
            bool flowIn() const { return m_flowIn; }
            bool flowOut() const { return m_flowOut; }
            Flow *flowInItem() const { return m_flowInItem; }
            Flow *flowOutItem() const { return m_flowOutItem; }
            RoundedRectangle *header() const { return m_header; }
            RoundedRectangle *content() const { return m_content; }

        public:
            void setFlowIn(bool f);
            void setFlowOut(bool f);
            void setFlowInItem(Flow *f);
            void setFlowOutItem(Flow *f);
            void setHeader(RoundedRectangle *h);
            void setContent(RoundedRectangle *c);

        signals:
            void flowInChanged(bool f);
            void flowOutChanged(bool f);
            void flowInItemChanged(Flow *f);
            void flowOutItemChanged(Flow *f);
            void headerChanged(RoundedRectangle *h);
            void contentChanged(RoundedRectangle *c);

        private:
            bool m_flowIn;
            bool m_flowOut;
            Flow *m_flowInItem;
            Flow *m_flowOutItem;
            RoundedRectangle *m_header;
            RoundedRectangle *m_content;

        private:
            FocusManagerIo m_inputs;
            FocusManagerIo m_outputs;
            QPointF m_offset;
			bool m_holdClik;
	        QPointF m_startPos;
	        CanvasNode* m_canvas;
            static GenericNode *m_selected;

        private:
            void updateInputs();
            void updateOutputs();

        protected:
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
        };
    }
}

#endif // GENERICNODE_H
