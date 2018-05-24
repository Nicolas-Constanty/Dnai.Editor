#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QQuickItem>
#include "command.h"

namespace dnai
{
	namespace commands
	{
		class MoveCommand : public Command
		{
		public:
            MoveCommand(QQuickItem* w, const QPointF& vec, bool save = false);

			virtual void execute() const override;
			virtual void executeSave() override;
			virtual void unExcute() const override;
			virtual QString infos() const override;

		private:
			QQuickItem* m_w;
            QPointF m_vec;
			QPointF m_lastPos;
		};
	}
}

#endif
