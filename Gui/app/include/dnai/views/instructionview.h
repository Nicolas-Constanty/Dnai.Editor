#ifndef INSTRUCTIONVIEW_H
#define INSTRUCTIONVIEW_H

#include "contextview.h"
#include "canvasnode.h"


namespace dnai
{
    namespace views
    {
        class InstructionView : public dnai::views::ContextView
        {
            Q_OBJECT
//            Q_PROPERTY(dnai::models::gui::declarable::Function *instructionModel READ instructionModel WRITE setInstructionModel NOTIFY instructionModelChanged)
        public:
            explicit InstructionView(QQuickItem *parent = nullptr);

            CanvasNode *canvas() const;
//        signals:
//			models::gui::declarable::Function *instructionModelChanged(models::gui::declarable::Function *model);

        public:
//            models::gui::declarable::Function *instructionModel() const;
//            void setInstructionModel(models::gui::declarable::Function *model);
        };
    }
}

#endif // INSTRUCTIONVIEW_H
