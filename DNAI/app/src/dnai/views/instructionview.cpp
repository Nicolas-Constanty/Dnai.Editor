#include "dnai/views/instructionview.h"

namespace dnai {
    namespace views {
        InstructionView::InstructionView(QQuickItem* parent) : ContextView("qrc:/resources/Components/NodeCanvas.qml", parent)
        {
        }

        CanvasNode* InstructionView::canvas() const
        {
            return dynamic_cast<CanvasNode*>(getView());
        }

//        models::gui::declarable::Function* InstructionView::instructionModel() const
//        {
//            return dynamic_cast<models::gui::declarable::Function *>(getModel("instructionModel"));
//        }

//        void InstructionView::setInstructionModel(models::gui::declarable::Function* model)
//        {
//            if (instructionModel() == model)
//                return;
////            addModel(static_cast<QObject*>(model), "instructionModel");
//            instructionModelChanged(model);
//        }
    }
}

