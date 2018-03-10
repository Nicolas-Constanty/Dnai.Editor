#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <stack>
#include <queue>

#include "dnai/interfaces/icommand.h"
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
            void registerCommand(interfaces::ICommand* cmd);

			/**
			* \brief Execute all the registers commands
			*/
			void execAll();

			/**
             * \brief Execute immediatlty the command
             * \param command 
             */
            void exec(interfaces::ICommand * command);

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

			/**
			 * \brief Assign the console view
			 * \param consoleView 
			 */
			void setConsoleView(views::Console *consoleView);
			/**
			 * \brief Return the console view
			 * \return const controllers::ConsoleController&
			 */
			const controllers::ConsoleController& console() const;

		private:
            std::stack<interfaces::ICommand *> m_undoList;
            std::stack<interfaces::ICommand *> m_redoList;
            std::queue<interfaces::ICommand *> m_doList;

			controllers::ConsoleController m_console;
			static CommandManager *m_instance;
		};
	}
}

#endif // COMMANDMANAGER_H
