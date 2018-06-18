#include "commandmanager.h"
#include "icommand.h"
#include "debugdecorator.h"

CommandManager::CommandManager()
{

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
        c->execute();
        m_undoList.push(c);
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
			command->execute();
			m_undoList.pop();
			m_redoList.push(command);
		}

	}
}
