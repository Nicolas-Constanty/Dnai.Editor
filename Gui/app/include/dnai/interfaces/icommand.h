#ifndef DNAI_INTERFACES_ICOMMAND_H
#define DNAI_INTERFACES_ICOMMAND_H

#include <QString>

namespace dnai
{
    namespace commands {
        class CommandManager;
        class DebugDecorator;
    }
    namespace interfaces
	{

		class ICommand
		{
		protected:
			virtual ~ICommand() = default;

			/**
			* \brief Execute the command
			*/
			virtual void execute() const = 0;

			/**
			* \brief Save current state of the command for the reverse unExcute()
			*/
			virtual void executeSave() = 0;

			/**
			* \brief Reverse the execute() function
			*/
			virtual void unExcute() const = 0;
			/**
			* \brief Get display info for this command
			* \return QString
			*/
			virtual QString infos() const = 0;
			/**
			* \brief Is the command is in a save state
			* \return bool
			*/
			virtual bool isSave() const = 0;
            friend class commands::CommandManager;
            friend class commands::DebugDecorator;
		};
	}
}


#endif // DNAI_INTERFACES_ICOMMAND_H
