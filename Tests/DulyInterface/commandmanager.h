#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include "icommand.h"
#include <stack>
#include <queue>


class CommandManager
{
public:
    CommandManager();
	void RegisterCommand(ICommand* cmd);
	void ExecAll();
	void Redo(int levels);
	void Undo(int levels);

private:
	std::stack<ICommand *> m_undoList;
	std::stack<ICommand *> m_redoList;
	std::queue<ICommand *> m_doList;
};

#endif // COMMANDMANAGER_H
