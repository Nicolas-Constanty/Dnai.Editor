#ifndef DNAI_VIEWS_VIEWELEMENT_H
#define DNAI_VIEWS_VIEWELEMENT_H

#include "dnai/interfaces/iviewelement.h"

namespace dnai
{
	namespace views
	{
		class ViewElement : public QQuickItem, public interfaces::IViewElement
		{
			Q_OBJECT
		public:
			void open() override;
			void close() override;
			QQuickItem* view() override;
		};
	}
}

#endif //DNAI_VIEWS_VIEWELEMENT_H