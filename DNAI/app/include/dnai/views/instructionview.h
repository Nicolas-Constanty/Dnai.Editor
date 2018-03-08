#ifndef INSTRUCTIONVIEW_H
#define INSTRUCTIONVIEW_H

#include "contextview.h"
#include "dnai/models/function.h"
#include "dnai/models/instruction.h"
#include "canvasnode.h"

namespace dnai
{
	namespace views
	{
		class InstructionView : public dnai::views::ContextView
		{
            Q_OBJECT
            Q_PROPERTY(dnai::models::Instruction *instructionModel READ instructionModel WRITE setInstructionModel NOTIFY instructionModelChanged)
		public:
            explicit InstructionView(QQuickItem *parent = nullptr);

			CanvasNode *canvas() const;
        signals:
            dnai::models::Instruction *instructionModelChanged(dnai::models::Instruction *model);

        public:
            dnai::models::Instruction *instructionModel() const;
            void setInstructionModel(dnai::models::Instruction *model);
		};
	}
}

#endif // INSTRUCTIONVIEW_H
