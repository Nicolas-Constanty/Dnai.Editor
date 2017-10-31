#include "commands/movecommand.h"
#include <QQuickItem>

namespace duly_gui
{
    namespace commands
    {
        MoveCommand::MoveCommand(QQuickItem *w, const QPointF &vec, bool save): Command("Move", save)
        {
            m_w = w;
            m_vec = vec;
        }

        void MoveCommand::execute() const
        {
            m_w->setPosition(m_vec);
        }

		void MoveCommand::executeSave()
        {
			m_lastPos = m_w->position();
			execute();
        }

        void MoveCommand::unExcute() const
        {
            m_w->setPosition(m_lastPos);
        }

        QString MoveCommand::infos() const
        {
            QString adresse;
            adresse.sprintf("%08p", m_w);
            return m_name + "(" + m_w->metaObject()->className() + "(" + adresse + ")" + ", " + QString::number(m_vec.x()) + ", " + QString::number(m_vec.y()) + ")";
        }
    }
}


