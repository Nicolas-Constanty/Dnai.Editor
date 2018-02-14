#include "dnai/views/instructionview.h"

dnai::views::InstructionView::InstructionView(QObject* parent) : ContextView(parent)
{
}

dnai::views::InstructionView::InstructionView(const QString& path, QObject* parent) : ContextView(path, parent)
{
}

dnai::models::Function* dnai::views::InstructionView::instructionModel() const
{
	return dynamic_cast<dnai::models::Function *>(getModel("instructionModel"));
}

void dnai::views::InstructionView::setInstructionModel(dnai::models::Function* model)
{
	if (instructionModel() == model)
		return;
	addModel(static_cast<QObject*>(model), "instructionModel");
	instructionModelChanged(model);
}
