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
        private:
            /**
             * \brief The CommandStack class behaves like a stack of interface::ICommand * but allow to remove any command from it
             */
            class CommandStack
            {
            public:
                CommandStack() = default;
                ~CommandStack() = default;

            public:
                void push(interfaces::ICommand *c)
                {
                    stack.push_back(c);
                }

                void pop()
                {
                    stack.pop_back();
                }

                interfaces::ICommand *top() const
                {
                    return stack.back();
                }

                bool empty() const
                {
                    return stack.empty();
                }

                void remove(interfaces::ICommand *c)
                {
                    stack.remove(c);
                }

            private:
                std::list<interfaces::ICommand *> stack;
            };

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

            /**
             * \brief Removes a command from undoList or redoList
             * \param c Command pointer to remove
             */
            void removeCommand(interfaces::ICommand *c);

		private:
            CommandStack m_undoList;
            CommandStack m_redoList;
            std::queue<interfaces::ICommand *> m_doList;

			controllers::ConsoleController m_console;
			static CommandManager *m_instance;
		};
	}
}

#endif // COMMANDMANAGER_H
