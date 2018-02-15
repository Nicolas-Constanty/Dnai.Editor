#include <QDebug>
#include "dnai/commands/debugdecorator.h"
#include "dnai/commands/commandmanager.h"
#include "dnai/views/console.h"

namespace dnai
{
	namespace commands
	{
		DebugDecorator::DebugDecorator(ICommand* decoratedCommand) : CommandDecorator(decoratedCommand)
		{
		}

		void DebugDecorator::execute() const
		{
			const auto console = CommandManager::Instance()->console();
			if (console.view()->mode() ==  views::Console::Verbose)
			{
				const auto message = "[Do]" + infos();
				qDebug() << message;
				console.writeLine(message);
			}
			m_decoratedCommand->execute();
		}

		void DebugDecorator::executeSave()
		{
            const auto message = "[#8BC34A]Save -> [Cmd]" + infos();
            qDebug() << message;
            CommandManager::Instance()->console().writeLine(message);
			m_decoratedCommand->executeSave();
		}

		bool DebugDecorator::isSave() const
		{
			return m_decoratedCommand->isSave();
		}

		void DebugDecorator::unExcute() const
		{
			const auto console = CommandManager::Instance()->console();
			if (console.view()->mode() == views::Console::Verbose)
			{
				const auto message = "[Undo]" + infos();
				qDebug() << message;
				console.writeLine(message);
			}
			m_decoratedCommand->unExcute();
		}

		QString DebugDecorator::infos() const
		{
			return m_decoratedCommand->infos();
		}
	}
}


