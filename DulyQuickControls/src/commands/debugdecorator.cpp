#include <QDebug>
#include "commands/debugdecorator.h"
#include "commands/commandmanager.h"

namespace duly_gui
{
	namespace commands
	{
		DebugDecorator::DebugDecorator(ICommand* decoratedCommand) : CommandDecorator(decoratedCommand)
		{
		}

		void DebugDecorator::execute() const
		{
			qDebug() << infos();
            CommandManager::Instance()->console().writeLine(infos());
			m_decoratedCommand->execute();
		}

		void DebugDecorator::executeSave()
		{
			qDebug() << infos();
			CommandManager::Instance()->console().writeLine("[#8BC34A]Save -> " + infos());
			m_decoratedCommand->executeSave();
		}

		bool DebugDecorator::isSave() const
		{
			return m_decoratedCommand->isSave();
		}

		void DebugDecorator::unExcute() const
		{
			m_decoratedCommand->unExcute();
		}

		QString DebugDecorator::infos() const
		{
			return m_decoratedCommand->infos();
		}
	}
}


