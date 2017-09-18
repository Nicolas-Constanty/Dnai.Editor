#include "debugdecorator.h"
#include <QDebug>


DebugDecorator::DebugDecorator(ICommand* decoratedCommand) : CommandDecorator(decoratedCommand)
{
}

void DebugDecorator::Execute() const
{
	qDebug() << "C++ Style Debug Message";
	m_decoratedCommand->Execute();
}

void DebugDecorator::UnExcute() const
{
	m_decoratedCommand->UnExcute();
}
