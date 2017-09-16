#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "icommand.h"
#include <QGraphicsItem>

class MoveCommand : public ICommand
{
public:
	MoveCommand(QGraphicsItem* w, const QPoint& vec);
	void Execute() const override;
	void UnExcute() const override;

private:
	QGraphicsItem* m_w;
	QPoint m_vec;
};

#endif
