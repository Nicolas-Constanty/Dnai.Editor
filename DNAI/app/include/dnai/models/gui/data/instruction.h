#ifndef DNAI_MODELS_GUI_DATA_INSTRUCTION_H
#define DNAI_MODELS_GUI_DATA_INSTRUCTION_H

#include <QList>
#include "dnai/enums/core/instructionid.h"
#include "dnai/models/gui/input.h"
#include "dnai/models/gui/output.h"
#include "dnai/models/gui/flow.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Instruction
				{
					QList<gui::Input*> inputs;
					QList<gui::Output*> outputs;
					Flow* flowIn = nullptr;
					Flow* flowOut = nullptr;
					qint32 instructionId = enums::QInstructionID::Instruction_ID::UNDEFINED;

					Instruction& operator=(const Instruction& other) = default;

					bool operator!=(const Instruction& other) const
					{
						return !(other == *this);
					}

					bool operator==(const Instruction& other) const
					{
						return (
							inputs == other.inputs
							&& outputs == other.outputs
							&& flowIn == other.flowIn
							&& instructionId == other.instructionId);
					}
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_INSTRUCTION_H