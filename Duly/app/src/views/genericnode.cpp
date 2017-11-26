#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>


#include "views/input.h"
#include "views/output.h"
#include "views/dulycanvas.h"
#include "views/genericnode.h"
#include "commands/movenodecommand.h"
#include "commands/commandmanager.h"
#include "dulyapp.h"

namespace duly_gui
{
	namespace views
	{
	
		GenericNode::GenericNode(QQuickItem *parent) :
            ScalableItem(parent)
		{
			m_canvas = static_cast<DulyApp *>(DulyApp::instance())->currentCanvas();
			m_canvas->focusManager().registerItem(this);
			setFlag(ItemHasContents, true);
			setAcceptHoverEvents(true);
			setAcceptedMouseButtons(Qt::LeftButton);
            setFlag(ItemAcceptsInputMethod, true);
		}

		void GenericNode::setFlowIn(bool f)
		{

			if (f == m_flowIn)
				return;
			m_flowIn = f;
			emit flowInChanged(f);
		}

		void GenericNode::setFlowOut(bool f)
		{
			if (f == m_flowOut)
				return;
			m_flowOut = f;
			emit flowOutChanged(f);
		}

		void GenericNode::setFlowInItem(Flow *f)
		{
			if (f == m_flowInItem || f == nullptr)
				return;
			m_flowInItem = f;
		}

		void GenericNode::setFlowOutItem(Flow *f)
		{
			if (f == m_flowOutItem || f == nullptr)
				return;
			m_flowOutItem = f;
		}

		void GenericNode::setHeader(RoundedRectangle *h)
		{
			if (h == m_header)
				return;
			m_header = h;
			m_header->setParent(this);
			emit headerChanged(h);
		}

		void GenericNode::setContent(RoundedRectangle *c)
		{
			if (c == m_content)
				return;
			m_content = c;
			m_content->setParent(this);
			emit contentChanged(c);
		}

        void GenericNode::setScaleFactor(qreal s)
        {
            if (s == m_scaleFactor)
                return;
            if (m_realPos == QPointF(-100000, -100000))
                m_realPos = position();
            m_scaleFactor = s;
            setScale(s);
            emit scaleFactorChanged(s);
            update();
        }

		void GenericNode::updateInputs()
		{
			auto list = m_inputs.getList();
			for (int i = 0; i < list.size(); i++)
			{
				auto input = dynamic_cast<Input *>(list.at(i));
				if (input && input->getLinkable()->isLink())
				{
					input->updateLink();
				}
			}
		}

		void GenericNode::updateOutputs()
		{
			auto list = m_outputs.getList();
			for (int i = 0; i < list.size(); i++)
			{
				auto output = dynamic_cast<Output *>(list.at(i));
				if (output && output->getLinkable()->isLink())
				{
					output->updateLink();
				}
			}
		}

		void GenericNode::mousePressEvent(QMouseEvent* event)
		{
            qDebug() << "hey";
			m_offset = QPointF(position() - mapToItem(m_canvas, event->pos()));
			if (this != parentItem()->childItems().last())
				stackAfter(parentItem()->childItems().last());
			m_header->setBorderColor(QColor(255, 170, 0, 255));
            m_content->setBorderColor(QColor(255, 170, 0, 255));
            m_holdClik = false;
		}

		void GenericNode::mouseMoveEvent(QMouseEvent* event)
		{
            const auto p(mapToItem(m_canvas, event->pos()) + m_offset);
            if (!m_holdClik)
            {
                m_holdClik = true;
                m_startPos = position();
            }
            commands::CommandManager::Instance()->registerCommand(new commands::MoveNodeCommand(this, p));
			commands::CommandManager::Instance()->execAll();
		}

        void GenericNode::move(const QPointF &vec)
        {
            setPosition(vec);
            updateInputs();
            updateOutputs();
            if (m_flowInItem && m_flowInItem->isVisible())
                m_flowInItem->updateLink();
            if (m_flowOutItem && m_flowOutItem->isVisible())
                m_flowOutItem->updateLink();
            m_realPos = realPos();
        }

		void GenericNode::mouseReleaseEvent(QMouseEvent *)
		{
            if (m_holdClik)
            {
                commands::CommandManager::Instance()->registerCommand(new commands::MoveNodeCommand(this, position(), true));
				commands::CommandManager::Instance()->execAll();
            }
			m_offset.setX(0);
			m_offset.setY(0);
			m_header->resetBorderColor();
            m_content->resetBorderColor();
            m_holdClik = false;
		}

		QSGNode *GenericNode::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
        {
            if (m_realPos == QPointF(-100000, -100000))
            {
                m_realPos = position();
                const auto p = m_canvas->origin() + QPointF(width() / 2, height() / 2);
                setTransformOriginPoint(p);
            }
            auto n = static_cast<QSGSimpleRectNode *>(oldNode);
			if (!n) {
                n = new QSGSimpleRectNode();
			}
            n->setColor(Qt::red);
			n->setRect(boundingRect());

			return n;
		}

		void GenericNode::componentComplete()
		{
            QQuickItem::componentComplete();
        }


        bool GenericNode::contains(const QPointF &point) const
        {
            return QQuickItem::contains(mapToItem(this, point));
        }
	}
}
