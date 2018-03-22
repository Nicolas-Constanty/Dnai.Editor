#include "dnai/views/viewelement.h"

namespace dnai
{
	namespace views
	{
		void ViewElement::open()
		{
			setVisible(true);
		}

		void ViewElement::close()
		{
		}

		QQuickItem* ViewElement::view()
		{
			return this;
		}
	}
}