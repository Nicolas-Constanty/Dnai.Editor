#include "dnai/link.h"
#include "dnai/app.h"
#include "dnai/eventutilities.h"
#include "dnai/views/linkablebezieritem.h"
#include "dnai/views/canvasnode.h"
#include "dnai/views/genericnode.h"

namespace dnai
{
	namespace views
	{
		LinkableBezierItem::LinkableBezierItem(QQuickItem *parent) : CustomShape(parent)
		, m_currentCurve(nullptr)
		, m_linkable(nullptr)
		, m_status(LinkStatus::Normal)
		{
			setAcceptHoverEvents(true);
			setAcceptedMouseButtons(Qt::LeftButton);
            setFlag(ItemAcceptsInputMethod, true);
            if (Editor::instance().selectedView())
            {
                const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
                if (view == nullptr)
                {
                    throw std::runtime_error("No canvas view found!");
                }
                m_canvas = dynamic_cast<CanvasNode *>(view);
            }
		}

		void LinkableBezierItem::mouseMoveEvent(QMouseEvent *event)
		{
            if (m_currentCurve == nullptr) return;
            const auto p(mapToItem(m_canvas->content(), event->pos()));
            m_currentCurve->setP4(p);
            auto qlist = m_canvas->focusManager().findFocused(p);
			if (qlist.empty())
            {
				return;
			}
            const auto node = dynamic_cast<GenericNode *>(qlist.at(0));
            if (node && node != getNode())
            {
                const auto p1(mapToItem(node, event->pos()));
                const auto cs = findLinkableBezierItem(node, p1);
                if (cs)
                {
                    cs->setIsHover(true);
                }
            }
		}

		void LinkableBezierItem::mousePressEvent(QMouseEvent *event)
		{
			if (EventUtilities::isHoverCircle(m_radius, event))
			{
                auto b = new BezierCurve(m_canvas->content());
                b->setPosition(getCanvasPos());
				b->setP1(QPoint(0, 0));
                QColor cb(curveColor());
                b->setFillColor(cb);
				const QColor c((cb.red() < 205 ? cb.red() + 50 : 255),
					(cb.green() < 205 ? cb.green() + 50 : 255),
					(cb.blue() < 205 ? cb.blue() + 50 : 255),
					cb.alpha());
				b->setDottedColor(c);
                m_currentCurve = b;
			}
		}

		void LinkableBezierItem::connect(LinkableBezierItem *a)
		{
			auto b = new BezierCurve(m_canvas->content());
            b->setPosition(getCanvasPos());
            b->setP1(QPoint(0, 0));
            const auto cb(curveColor());
			b->setFillColor(cb);
			const auto co = m_linkable->connect(a->getLinkable(), b);
			if (co)
			{
                const auto p2(a->getCanvasPos());
				b->setP4(p2);
				b->setDotted(false);
                b->setBack();
				m_currentCurve = nullptr;
			}
		}

		void LinkableBezierItem::mouseReleaseEvent(QMouseEvent *event)
		{
			if (event->button() != Qt::LeftButton || m_currentCurve == nullptr)
				return;
            const auto p(mapToItem(m_canvas->content(), event->pos()));
            auto qlist = m_canvas->focusManager().findFocused(p);
			if (qlist.size() == 0)
			{
				delete(m_currentCurve);
                m_currentCurve = nullptr;
				afterRealease(nullptr);
				return;
			}
            const auto node = dynamic_cast<GenericNode *>(qlist.at(0));
            if (node && node != getNode())
			{
				const auto p1(mapToItem(node, event->pos()));
				const auto cs = findLinkableBezierItem(node, p1);
				if (cs)
				{
                    const auto c = m_linkable->asyncConnect(cs->getLinkable());
					if (c == nullptr)
					{
                        delete(m_currentCurve);
                    }
                    afterRealease(c);
					m_currentCurve = nullptr;
					return;
				}
			}
            else if (node)
            {
                delete(m_currentCurve);
                m_currentCurve = nullptr;
                afterRealease(nullptr);
                return;
            }
			afterRealease(nullptr);
			delete(m_currentCurve);
			m_currentCurve = nullptr;
		}

		void LinkableBezierItem::afterRealease(Link *)
        {}


		void LinkableBezierItem::unlinkAll()
        {
            auto list = m_linkable->links();
            for (auto l : list)
            {
                auto lb = dynamic_cast<LinkableBezierItem *>(dynamic_cast<BaseLinkable *>(l->L1 == m_linkable ? l->L2 : l->L1)->parent());
                if (lb->getLinkable()->links().size() < 2)
                    lb->setIsLink(false);
            }
            m_linkable->unlinkAll();
        }

        void LinkableBezierItem::asyncUnlinkAll()
        {
            unlinkAll();
        }
	}
	
}
