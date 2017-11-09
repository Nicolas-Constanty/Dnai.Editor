#ifndef ISCALABLE_H
#define ISCALABLE_H

#include <QPointF>

namespace duly_gui
{
	class IScalable
	{
	public:
		virtual qreal scaleFactor() const = 0;
		virtual QPointF scalePos() const = 0;
		virtual QPointF realPos() const = 0;
	};
}

#endif // ISCALABLE_H
