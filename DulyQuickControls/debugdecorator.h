#ifndef DEBUGDECORATOR_H
#define DEBUGDECORATOR_H
#include "commanddecorator.h"

class DebugDecorator : public CommandDecorator
{
public:
	DebugDecorator(ICommand *decoratedCommand);

	void Execute() const override;
	void UnExcute() const override;

};

#endif // DEBUGDECORATOR_H