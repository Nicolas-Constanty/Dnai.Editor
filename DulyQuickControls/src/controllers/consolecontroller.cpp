#include "controllers/consolecontroller.h"

namespace duly_gui
{
	namespace controllers
	{
		ConsoleController::ConsoleController()
		{
		}

		void ConsoleController::writeLine(const QString& text) const
		{
			if (m_view)
			{
				m_view->addText(text);
			}
		}

        void ConsoleController::setConsole(views::Console *c)
        {
            if (c == m_view)
                return;
            m_view = c;
        }
	}
}
