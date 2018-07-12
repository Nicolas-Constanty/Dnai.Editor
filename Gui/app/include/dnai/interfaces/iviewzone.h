#ifndef DNAI_INTERFACES_IVIEWZONE_H
#define DNAI_INTERFACES_IVIEWZONE_H

#include "iviewelement.h"
#include "iserializable.h"

namespace dnai
{
	namespace interfaces
	{
		class IViewZone : public ISerializable
		{
		public:
			virtual ~IViewZone() = default;
			enum SplitDirection
			{
				TOP,
				BOTTOM,
				LEFT,
				RIGHT
			};
			virtual void open() = 0;
			virtual void close() = 0;
			virtual void focusNext() = 0;
			virtual void focusPrev() = 0;
			virtual void addView(IViewElement *view) = 0;
			virtual const QList<IViewElement *> &views() const = 0;
			virtual void removeView() = 0;
			virtual void split(SplitDirection dir) = 0;
		};
	}
}

#endif //DNAI_INTERFACES_IVIEWZONE_H
