#ifndef MOVENODECOMMAND_H
#define MOVENODECOMMAND_H

#include <QQuickItem>

#include "command.h"
#include "dnai/views/genericnode.h"

namespace dnai
{
	namespace commands
	{
		/**
		* \brief MoveNodeCommand allow to move GenericNode in canvas
		*/
        class MoveNodeCommand : public Command
		{
		public:
            MoveNodeCommand(views::GenericNode * n, const QPointF& vec, bool save = false);

			//Override ICommand functions
        public:
	        virtual void execute() const override;
	        virtual void executeSave() override;
	        virtual void unExcute() const override;
	        virtual QString infos() const override;

		private:
            views::GenericNode * m_n;
            QPointF m_vec;
			QPointF m_lastPos;
		};
	}
}

#endif
