#include "commands/movenodecommand.h"
#include <QQuickItem>

namespace duly_gui
{
    namespace commands
    {
        MoveNodeCommand::MoveNodeCommand(views::GenericNode *n, const QPointF &vec, bool save): Command("Move", save)
        {
            m_n = n;
            m_vec = vec;
        }

        void MoveNodeCommand::execute() const
        {
            m_n->Move(m_vec);
        }

        void MoveNodeCommand::executeSave()
        {
            m_lastPos = m_n->position();
			execute();
        }

        void MoveNodeCommand::unExcute() const
        {
            m_n->Move(m_lastPos);
        }

        QString MoveNodeCommand::infos() const
        {
            QString adresse;
            adresse.sprintf("%08p", m_n);
            return m_name + "(" + m_n->metaObject()->className() + "(" + adresse + ")" + ", " + QString::number(m_vec.x()) + ", " + QString::number(m_vec.y()) + ")";
        }
    }
}


