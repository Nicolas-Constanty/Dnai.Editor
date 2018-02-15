#include <qglobal.h>
#include "dnai/eventutilities.h"

namespace dnai
{
	EventUtilities::EventUtilities()
	{

	}

	bool EventUtilities::isHoverRectF(const QRectF &r, QMouseEvent *e)
	{
		return r.contains(e->pos());
	}

	bool EventUtilities::isHoverRect(const QRect &r, QMouseEvent *e)
	{
		return r.contains(e->pos());
	}

	bool EventUtilities::isHoverCircle(const qreal ra, QMouseEvent *e)
	{
		const auto r = ra + ra / 2.5;
		const auto p = e->pos();
		const auto dx = qAbs(p.x() - r);
		if (dx > r) return false;
		const auto dy = qAbs(p.y() - r);
		if (dy > r) return false;
		if (dx + dy <= r) return true;
		return (dx*dx + dy*dy <= r*r);
	}

}
