#ifndef DNAI_MODELS_GUI_DATA_FUNCTION_H
#define DNAI_MODELS_GUI_DATA_FUNCTION_H

#include "entity.h"
#include "instruction.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/interfaces/iinstruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Function : Entity, Instruction
				{
					QList<interfaces::IInstruction*> instructions;
					QList<declarable::Variable*> variables;

                    Function& operator=(const Function& other) = default;

					bool operator!=(const Function& other) const
					{
						return !(*this == other);
					}

					bool operator==(const Function& other) const
					{
						return (Instruction::operator==(other) && instructions == other.instructions && variables == other.variables);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_FUNCTION_H
