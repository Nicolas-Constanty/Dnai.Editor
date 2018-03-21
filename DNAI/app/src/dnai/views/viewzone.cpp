#include "dnai/views/viewzone.h"
#include "dnai/editor.h"

namespace dnai
{
	namespace views
    {
        ViewZone::ViewZone(QQuickItem *parent) : QQuickItem(parent)
        {
			Editor::instance().addView(this);
        }

        void ViewZone::serialize(QJsonObject& obj) const
		{
		}

		void ViewZone::_deserialize(const QJsonObject& obj)
		{
		}

		void ViewZone::open()
		{
		}

		void ViewZone::close()
		{
		}

		void ViewZone::focusNext()
		{
		}

		void ViewZone::focusPrev()
		{
		}

		void ViewZone::addView(interfaces::IViewElement* view)
		{
		}

		const QList<interfaces::IViewElement*>& ViewZone::views() const
		{
			return m_views;
		}

		void ViewZone::removeView()
		{

		}

		void ViewZone::split(SplitDirection dir)
		{
		}
	}
}
