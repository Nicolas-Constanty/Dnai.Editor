#include "dnai/controllers/propertypanel.h"
#include "dnai/commands/openpropertypanel.h"

namespace dnai
{
	namespace controllers
	{
		PropertyPanel::PropertyPanel() : AController<dnai::models::Entity>("qrc:/resources/Panels/Properties.qml")
		{
		}

		models::IClone* PropertyPanel::clone() const
		{
			return new PropertyPanel(*this);
		}

		QQuickItem* PropertyPanel::createView()
		{
			return dynamic_cast<QQuickItem*>(App::createQmlObject(m_viewPath));
		}

		commands::ICommand* PropertyPanel::createCommand()
		{
			return new commands::OpenPropertyPanel(this, true);
        }
	}
}
