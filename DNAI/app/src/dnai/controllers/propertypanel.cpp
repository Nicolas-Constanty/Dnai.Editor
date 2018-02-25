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
            return nullptr;
		}

        commands::ICommand* PropertyPanel::createCommand() const
		{
            return new commands::OpenPropertyPanel(this, true);
        }
	}
}
