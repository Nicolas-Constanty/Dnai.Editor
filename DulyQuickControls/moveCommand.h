#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "icommand.h"
#include <QQuickItem>

class MoveCommand : public ICommand
{
public:
    MoveCommand(QQuickItem* w, const QPoint& vec);

	/**
	* \brief Execute the command
	*/
	void execute() const override;

	/**
	* \brief Reverse the command
	*/
	void unExcute() const override;

private:
    QQuickItem* m_w;
	QPoint m_vec;
};

#endif
