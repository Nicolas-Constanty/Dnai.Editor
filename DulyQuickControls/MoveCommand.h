#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "icommand.h"
#include <QQuickItem>

class MoveCommand : public ICommand
{
public:
    MoveCommand(QQuickItem* w, const QPoint& vec);
	void Execute() const override;
	void UnExcute() const override;

private:
    QQuickItem* m_w;
	QPoint m_vec;
};

#endif
