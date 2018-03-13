#ifndef DNAI_INTERFACES_IVIEWELEMENT_H
#define DNAI_INTERFACES_IVIEWELEMENT_H
#include <QQuickItem>

namespace dnai
{
	namespace interfaces
	{
		class IViewElement
		{
		public:
			virtual ~IViewElement() = default;
			virtual void open() = 0;
			virtual void close() = 0;
			virtual QQuickItem *view() = 0;
		};
	}
}

#endif // DNAI_INTERFACES_IVIEWELEMENT_H