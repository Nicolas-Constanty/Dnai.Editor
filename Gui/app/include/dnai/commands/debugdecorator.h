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

			//Override ICommand functions
		public:
            void execute() const override;
            void executeSave() override;
            void unExcute() const override;
            bool isSave() const override;
            QString infos() const override;
		};

	}
}

#endif // DEBUGDECORATOR_H
