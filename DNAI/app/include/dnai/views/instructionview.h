#ifndef INSTRUCTIONVIEW_H
#define INSTRUCTIONVIEW_H

#include "contextview.h"
#include "dnai/models/function.h"
#include "canvasnode.h"

namespace dnai
{
	namespace views
	{
		class InstructionView : public dnai::views::ContextView
		{
            Q_OBJECT
            Q_PROPERTY(dnai::models::Function *instructionModel READ instructionModel WRITE setInstructionModel NOTIFY instructionModelChanged)
		public:
			explicit InstructionView(QObject *parent = nullptr);
			explicit InstructionView(const QString &path, QObject *parent = nullptr);

			CanvasNode *canvas() const;
        signals:
            dnai::models::Function *instructionModelChanged(dnai::models::Function *model);

        public:
            dnai::models::Function *instructionModel() const;
            void setInstructionModel(dnai::models::Function *model);
		};
	}
}

#endif // INSTRUCTIONVIEW_H
