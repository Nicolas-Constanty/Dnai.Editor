#include "commands/commanddecorator.h"

namespace duly_gui
{
	namespace commands
	{
		CommandDecorator::CommandDecorator(ICommand* decoratedCommand)
			: m_decoratedCommand(decoratedCommand) {}
	}
}

