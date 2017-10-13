#include <QDebug>
#include "commands/debugdecorator.h"

namespace duly_gui
{
	namespace commands
	{
		DebugDecorator::DebugDecorator(ICommand* decoratedCommand) : CommandDecorator(decoratedCommand)
		{
		}

		void DebugDecorator::execute() const
		{
			qDebug() << "C++ Style Debug Message";
			m_decoratedCommand->execute();
		}

		void DebugDecorator::unExcute() const
		{
			m_decoratedCommand->unExcute();
		}
	}
}


