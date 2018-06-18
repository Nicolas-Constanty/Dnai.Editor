#include "debugdecorator.h"
#include <QDebug>


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
