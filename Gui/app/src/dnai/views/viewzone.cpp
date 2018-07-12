#include "dnai/views/viewzone.h"
#include "dnai/editor.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"

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
            Q_UNUSED(obj)
            exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
		}

		void ViewZone::_deserialize(const QJsonObject& obj)
		{
            Q_UNUSED(obj)
            exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
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
            m_views.append(view);
		}

		const QList<interfaces::IViewElement*>& ViewZone::views() const
		{
			return m_views;
		}

		void ViewZone::removeView()
		{}

		void ViewZone::split(SplitDirection dir)
		{
            Q_UNUSED(dir)
            exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
		}
	}
}
