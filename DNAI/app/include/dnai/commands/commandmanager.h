#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include <queue>

#include "icommand.h"
#include "dnai/controllers/consolecontroller.h"

namespace dnai
{
	namespace commands
	{
		class CommandManager
		{
		public:
			CommandManager();

			static CommandManager *Instance();
			/**
			* \brief Register a command
			* \param cmd
			*/
			void registerCommand(ICommand* cmd);

			/**
			* \brief Execute all the registers commands
			*/
			void execAll();

			void exec(ICommand *command);

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

			void setConsoleView(views::Console *consoleView);
			const controllers::ConsoleController &console() const { return  m_console;  }

		private:
			std::stack<ICommand *> m_undoList;
			std::stack<ICommand *> m_redoList;
			std::queue<ICommand *> m_doList;

			controllers::ConsoleController m_console;
			static CommandManager *m_instance;
		};
	}
}

#endif // COMMANDMANAGER_H
