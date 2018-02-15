#ifndef MOVENODECOMMAND_H
#define MOVENODECOMMAND_H

#include <QQuickItem>

#include "command.h"
#include "dnai/views/genericnode.h"

namespace dnai
{
	namespace commands
	{
        class MoveNodeCommand : public Command
		{
		public:
            MoveNodeCommand(views::GenericNode * n, const QPointF& vec, bool save = false);

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
            views::GenericNode * m_n;
            QPointF m_vec;
			QPointF m_lastPos;
		};
	}
}

#endif
