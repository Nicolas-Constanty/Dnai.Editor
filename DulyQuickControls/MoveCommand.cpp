#include "MoveCommand.h"


MoveCommand::MoveCommand(QQuickItem *w, const QPoint &vec)
{
	m_w = w;
	m_vec = vec;
}

void MoveCommand::Execute() const
{
    m_w->setPosition(m_w->position() + m_vec);
}

void MoveCommand::UnExcute() const
{
    m_w->setPosition(m_w->position() - m_vec);
}

