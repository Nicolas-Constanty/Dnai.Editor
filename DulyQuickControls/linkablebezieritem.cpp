#include "linkablebezieritem.h"
#include "dulycanvas.h"
#include "genericnode.h"
#include "eventutilities.h"

LinkableBezierItem::LinkableBezierItem(QQuickItem *parent) : CustomShape(parent), m_currentCurve(nullptr),
                                                             m_linkable(nullptr)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(ItemAcceptsInputMethod, true);
}


const QColor &LinkableBezierItem::colorLink() const
{
	return m_fillColor;
}

void LinkableBezierItem::mouseMoveEvent(QMouseEvent *event)
{
	const auto p(mapToItem(DulyCanvas::Instance, event->pos()));
	m_currentCurve->setP4(p);
}

void LinkableBezierItem::mousePressEvent(QMouseEvent *event)
{
    if (EventUtilities::isHoverCircle(m_radius, event))
	{
		auto b = new BezierCurve(DulyCanvas::Instance);
        b->setPosition(getCanvasPos());
		b->setP1(QPoint(0, 0));
		QColor cb(colorLink());
        b->setFillColor(cb);
		const QColor c((cb.red() < 205 ? cb.red() + 50 : 255),
			(cb.green() < 205 ? cb.green() + 50 : 255),
			(cb.blue() < 205 ? cb.blue() + 50 : 255),
			cb.alpha());
		b->setDottedColor(c);
		m_currentCurve = b;
	}
}

void LinkableBezierItem::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton || m_currentCurve == nullptr)
		return;
	const auto p(mapToItem(DulyCanvas::Instance, event->pos()));
	auto qlist = DulyCanvas::Instance->focusManager().findFocused(p);
	if (qlist.size() == 0)
	{
		delete(m_currentCurve);
		m_currentCurve = nullptr;
		return;
	}
	const auto node = dynamic_cast<GenericNode *>(qlist.at(0));
	if (node && node != getNode())
	{
		const auto p1(mapToItem(node, event->pos()));
		const auto cs = findLinkableBezierItem(node, p1);
		if (cs)
        {
			const auto c = m_linkable->connect(cs->getLinkable(), m_currentCurve);
			if (c == nullptr)
				delete(m_currentCurve);
			else
            {
                const auto p2(cs->getCanvasPos());
				m_currentCurve->setP4(p2);
				m_currentCurve->setDotted(false);
                afterRealease(cs);
			}
			m_currentCurve = nullptr;
			return;
		}
	}
	delete(m_currentCurve);
	m_currentCurve = nullptr;
}

void LinkableBezierItem::afterRealease(LinkableBezierItem *)
{}
