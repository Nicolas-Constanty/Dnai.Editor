#include "dnai/commands/openpropertypanel.h"
#include "dnai/controllers/propertypanel.h"

namespace dnai
{
	namespace commands
	{
		OpenPropertyPanel::OpenPropertyPanel(controllers::PropertyPanel *panel, const bool save)
			: Command("OPEN_PROPERTY_PANEL", save), m_panel(panel), m_savedPanel(nullptr)
		{
		}

		void OpenPropertyPanel::execute() const
		{
            m_panel->create(nullptr);
		}

		void OpenPropertyPanel::unExcute() const
		{
			*m_panel = *m_savedPanel;
			delete m_savedPanel;
		}

		void OpenPropertyPanel::executeSave()
		{
			m_savedPanel = dynamic_cast<controllers::PropertyPanel*>(m_panel->clone());
			execute();
		}

		OpenPropertyPanel::~OpenPropertyPanel()
		{
			delete m_savedPanel;
		}
	}
}
