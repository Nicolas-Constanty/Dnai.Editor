#include "dnai/commands/commandmanager.h"
#include "dnai/commands/debugdecorator.h"
#include "dnai/editor.h"
#include "dnai/project.h"

namespace dnai
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

        void CommandManager::registerCommand(interfaces::ICommand *cmd)
		{
			if (m_console.view() && m_console.view()->isVisible())
                m_doList.push(new DebugDecorator(cmd));
			else
				m_doList.push(cmd);

            while (!m_redoList.empty()) {
	            const auto r = m_redoList.top();
                delete r;
                m_redoList.pop();
            }
		}

        void CommandManager::exec(interfaces::ICommand* c)
        {
            if (m_console.view() && m_console.view()->isVisible())
            {
                c = new DebugDecorator(c);
            }
			if (c->isSave())
			{
                qDebug() << "Execute save";
				c->executeSave();
				m_undoList.push(c);
                Project *dnaiProject = dynamic_cast<Project *>(Editor::instance().solution()->seletedProject());
                if (dnaiProject) {
                    dnaiProject->setSaved(false);
                }
			}
			else
                c->execute();
		}


		void CommandManager::execAll()
		{
			while (!m_doList.empty())
            {
                interfaces::ICommand *c = m_doList.front();
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
                    if (m_console.view() && m_console.view()->isVisible() && !dynamic_cast<DebugDecorator *>(command))
                        command = new DebugDecorator(command);
                    command->execute();
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
                    if (m_console.view() && m_console.view()->isVisible() && !dynamic_cast<DebugDecorator *>(command))
                        command = new DebugDecorator(command);
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

		const controllers::ConsoleController& CommandManager::console() const
		{
			return m_console;
		}

        void CommandManager::removeCommand(interfaces::ICommand *c)
        {
            if (!c->isSave())
                return;

            m_undoList.remove(c);
            m_redoList.remove(c);
        }
	}
}
