#include "commands/moveCommand.h"

namespace duly_gui
{
	namespace commands
	{
		MoveCommand::MoveCommand(QQuickItem *w, const QPoint &vec)
		{
			m_w = w;
			m_vec = vec;
		}

		void MoveCommand::execute() const
		{
			m_w->setPosition(m_w->position() + m_vec);
		}

		void MoveCommand::unExcute() const
		{
			m_w->setPosition(m_w->position() - m_vec);
		}

	}
}


