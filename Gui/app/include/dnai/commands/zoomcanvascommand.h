#ifndef ZOOMCANVASCOMMAND_H
#define ZOOMCANVASCOMMAND_H

#include <QQuickItem>

#include "command.h"
#include "dnai/views/canvasnode.h"

namespace dnai
{
    namespace commands
    {
        class ZoomCanvasCommand : public Command
        {
        public:
            ZoomCanvasCommand(views::CanvasNode * c, const double& scale, const QPointF &offset);

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
            views::CanvasNode * m_canvas;
            double m_scale;
            QPointF m_offset;
        };
    }
}

#endif // ZOOMCANVASCOMMAND_H
