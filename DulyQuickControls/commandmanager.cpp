#include "commandmanager.h"
#include "icommand.h"
#include "debugdecorator.h"

CommandManager::CommandManager()
{

}

void CommandManager::RegisterCommand(ICommand *cmd)
{
#ifndef  Debug
	m_doList.push(new DebugDecorator(cmd));
#else
	m_doList.push(cmd);
#endif
	
}

void CommandManager::ExecAll()
{
	while (!m_doList.empty())
	{
        ICommand *c = m_doList.front();
        c->Execute();
        m_undoList.push(c);
		m_doList.pop();
	}
}

void CommandManager::Redo(int levels)
{
	for (int i = 1; i <= levels; i++)
	{
		if (!m_redoList.empty())
		{
			ICommand *command = m_redoList.top();
			command->Execute();
			m_redoList.pop();
			m_undoList.push(command);
		}

	}
}

void CommandManager::Undo(int levels)
{
	for (int i = 1; i <= levels; i++)
	{
		if (!m_undoList.empty())
		{
			ICommand *command = m_undoList.top();
			command->Execute();
			m_undoList.pop();
			m_redoList.push(command);
		}

	}
}
