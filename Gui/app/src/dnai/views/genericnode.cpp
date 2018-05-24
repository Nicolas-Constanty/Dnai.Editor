#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>
#include <QSizeF>


#include "dnai/views/input.h"
#include "dnai/views/output.h"
#include "dnai/views/canvasnode.h"
#include "dnai/views/genericnode.h"
#include "dnai/commands/movenodecommand.h"
#include "dnai/commands/commandmanager.h"
#include "dnai/app.h"

namespace dnai
{
	namespace views
	{
        GenericNode *GenericNode::m_selected = nullptr;
		GenericNode::GenericNode(QQuickItem *parent) :
            QQuickItem(parent)
        {
	        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
			if (!view)
			{
				throw std::runtime_error("No canvas view found!");
			}
			m_canvas = dynamic_cast<CanvasNode *>(view);
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
            m_offset = QPointF(position() - mapToItem(m_canvas->content(), event->pos()));
			if (this != parentItem()->childItems().last())
				stackAfter(parentItem()->childItems().last());
            if (m_selected && m_selected != this)
            {
                m_selected->resetBorderColor();
            }
			m_header->setBorderColor(QColor(255, 170, 0, 255));
            m_content->setBorderColor(QColor(255, 170, 0, 255));
            m_selected = this;
            m_holdClik = false;
        }

        void GenericNode::resetSelected()
        {
            if (m_selected)
                m_selected->resetBorderColor();
            m_selected = nullptr;
        }

        void GenericNode::resetBorderColor()
        {
            m_content->resetBorderColor();
            m_header->resetBorderColor();
        }

		void GenericNode::mouseMoveEvent(QMouseEvent* event)
		{
            const auto p(mapToItem(m_canvas->content(), event->pos()) + m_offset);
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
            m_holdClik = false;
		}

        QSGNode *GenericNode::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
        {
            auto n = static_cast<QSGSimpleRectNode *>(oldNode);
			if (!n) {
                n = new QSGSimpleRectNode();
				const auto p = m_canvas->origin() + QPointF(width() / 2, height() / 2);
				setTransformOriginPoint(p);
			}
            n->setColor(Qt::transparent);
			n->setRect(boundingRect());

			return n;
		}

		void GenericNode::componentComplete()
		{
            QQuickItem::componentComplete();
        }

/*
        bool GenericNode::contains(const QPointF &point) const
        {
            auto p = mapToItem(m_canvas, point);
            auto ref = position();
            qDebug() << p << ref << realPos() << m_canvas->mapToItem(m_canvas, ref) << (p.x() >= ref.x()
                        && p.y() >= ref.y());

            return p.x() >= ref.x()
                    && p.y() >= ref.y()
                    && p.x() <= ref.x() + width() * scaleFactor()
                    && p.y() <= ref.y() + height() * scaleFactor();
        }*/
	}
}
