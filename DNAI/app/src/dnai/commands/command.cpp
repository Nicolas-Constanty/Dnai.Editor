#include "dnai/commands/command.h"

namespace dnai
{
	namespace commands
	{
        Command::Command(const QString &name, bool save) :
            QEvent(static_cast<QEvent::Type>(QEvent::registerEventType())),
            m_name(name),
            m_save(save)
		{
		}

		void Command::execute() const
		{
			
		}

		void Command::unExcute() const
		{
			
		}

		void Command::executeSave()
		{
		}

		bool Command::isSave() const
		{
			return m_save;
		}

		QString Command::infos() const
		{
			return m_name + "()";
        }
	}
}
