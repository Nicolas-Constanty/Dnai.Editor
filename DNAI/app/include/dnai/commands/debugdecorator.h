#ifndef DEBUGDECORATOR_H
#define DEBUGDECORATOR_H
#include "commanddecorator.h"

namespace dnai
{
	namespace commands
	{
		class DebugDecorator : public CommandDecorator
		{
		public:
			explicit DebugDecorator(ICommand *decoratedCommand);

			/**
			* \brief Execute the command
			*/
			void execute() const override;
			void executeSave() override;
			bool isSave() const override;
			/**
			* \brief Reverse the command
			*/
			void unExcute() const override;
	
			QString infos() const override;

		};

	}
}

#endif // DEBUGDECORATOR_H