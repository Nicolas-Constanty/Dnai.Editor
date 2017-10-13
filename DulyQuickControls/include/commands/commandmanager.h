#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H


#include "icommand.h"
#include <stack>
#include <queue>

namespace duly_gui
{
	namespace commands
	{
		class CommandManager
		{
		public:
			CommandManager();

			/**
			* \brief Register a command
			* \param cmd
			*/
			void registerCommand(ICommand* cmd);

			/**
			* \brief Execute all the registers commands
			*/
			void execAll();

			/**
			* \brief Exectute the next command
			* \param levels
			*/
			void redo(int levels);

			/**
			* \brief Execute the last command
			* \param levels
			*/
			void undo(int levels);

		private:
			std::stack<ICommand *> m_undoList;
			std::stack<ICommand *> m_redoList;
			std::queue<ICommand *> m_doList;
		};
	}
}

#endif // COMMANDMANAGER_H
