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

			/**
			* \brief Execute the command
			*/
			void execute() const override;
			void executeSave() override;

			/**
			* \brief Reverse the command
			*/
			void unExcute() const override;

			QString infos() const override;

		private:
			QQuickItem* m_w;
            QPointF m_vec;
			QPointF m_lastPos;
		};
	}
}

#endif
