#include "dnai/commands/commanddecorator.h"

namespace dnai
{
	namespace commands
	{
		CommandDecorator::CommandDecorator(ICommand* decoratedCommand)
			: m_decoratedCommand(decoratedCommand) {}
	}
}

