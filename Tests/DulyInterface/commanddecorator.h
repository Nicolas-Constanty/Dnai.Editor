#ifndef COMMANDDECORATOR_H
#define COMMANDDECORATOR_H

#include "icommand.h"

class CommandDecorator : public ICommand
{
protected:
    ICommand *m_decoratedCommand;

public:
	explicit CommandDecorator(ICommand *decoratedCommand);
};

#endif // COMMANDDECORATOR_H
