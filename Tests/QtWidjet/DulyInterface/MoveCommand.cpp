#include "MoveCommand.h"


MoveCommand::MoveCommand(QGraphicsItem *w, const QPoint &vec)
{
	m_w = w;
	m_vec = vec;
}

void MoveCommand::Execute() const
{
	m_w->setPos(m_w->pos() + m_vec);
}

void MoveCommand::UnExcute() const
{
	m_w->setPos(m_w->pos() - m_vec);
}

