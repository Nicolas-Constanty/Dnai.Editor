#include "dnai/controllers/consolecontroller.h"

namespace dnai
{
	namespace controllers
	{
		ConsoleController::ConsoleController()
		{
            m_view = nullptr;
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
            if (c != nullptr && c == m_view)
                return;
            m_view = c;
        }
	}
}
