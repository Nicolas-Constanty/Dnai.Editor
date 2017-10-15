#include "views/console.h"
#include "commands/commandmanager.h"

namespace duly_gui
{
	namespace views
	{
        Console::Console(QQuickItem* parent) : QQuickItem(parent)
		{
			commands::CommandManager::Instance()->setConsoleView(this);
        }

		void Console::addText(const QString& text)
		{
			if (m_text.size() > 10)
				m_text.removeFirst();
			m_text.append(text);
			emit textChanged(m_text);
		}

		void Console::setText(const QStringList& text)
        {
			m_text = text;
			emit textChanged(m_text);
		}
	}
}
