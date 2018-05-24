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
			virtual void execute() const override;
			virtual void executeSave() override;
			virtual void unExcute() const override;
			virtual bool isSave() const override;
			virtual QString infos() const override;

		};

	}
}

#endif // DEBUGDECORATOR_H