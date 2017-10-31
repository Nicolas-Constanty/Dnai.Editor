#include "commands/commandmanager.h"
#include "commands/debugdecorator.h"

namespace duly_gui
{
	namespace commands
	{
		CommandManager *CommandManager::m_instance = nullptr;
        CommandManager::CommandManager()
		{
		}

		CommandManager* CommandManager::Instance()
		{
			if (m_instance)
				return m_instance;
			m_instance = new CommandManager();
			return  m_instance;
		}

		void CommandManager::registerCommand(ICommand *cmd)
		{
#ifndef  Debug
			m_doList.push(new DebugDecorator(cmd));
#else
			m_doList.push(cmd);
#endif

		}

		void CommandManager::execAll()
		{
			while (!m_doList.empty())
			{
				ICommand *c = m_doList.front();
				if (c->isSave())
				{
					c->executeSave();
					m_undoList.push(c);
				}
                else
                    c->execute();
				m_doList.pop();
			}
		}

		void CommandManager::redo(int levels)
		{
			for (int i = 1; i <= levels; i++)
			{
				if (!m_redoList.empty())
				{
					auto command = m_redoList.top();
					command->executeSave();
					m_redoList.pop();
					m_undoList.push(command);
				}

			}
		}

		void CommandManager::undo(int levels)
		{
			for (int i = 1; i <= levels; i++)
			{
				if (!m_undoList.empty())
				{
					auto command = m_undoList.top();
					command->unExcute();
					m_undoList.pop();
					m_redoList.push(command);
				}

			}
		}

		void CommandManager::setConsoleView(views::Console* consoleView)
		{
			m_console.setConsole(consoleView);
		}
	}
}
