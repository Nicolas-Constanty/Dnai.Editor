#ifndef DNAI_MODELS_GUI_DATA_FUNCTION_H
#define DNAI_MODELS_GUI_DATA_FUNCTION_H

#include "entity.h"
#include "instruction.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/instruction.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Function : Entity
				{
					QList<models::Entity*> inputs;
					QList<models::Entity*> outputs;
					QList<models::gui::Instruction*> instructions;
					QList<declarable::Variable*> variables;
					QList<models::gui::IoLink *> iolinks;

                    Function& operator=(const Function& other) = default;

					bool operator!=(const Function& other) const
					{
						return !(*this == other);
					}

					bool operator==(const Function& other) const
					{
						return (instructions == other.instructions && variables == other.variables);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_FUNCTION_H
