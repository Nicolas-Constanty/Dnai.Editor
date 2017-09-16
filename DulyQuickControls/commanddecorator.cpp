#include "commanddecorator.h"

CommandDecorator::CommandDecorator(ICommand* decoratedCommand)
: m_decoratedCommand(decoratedCommand) {}
