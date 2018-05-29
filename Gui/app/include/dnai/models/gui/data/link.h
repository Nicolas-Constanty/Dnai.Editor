#ifndef DNAI_MODELS_GUI_DATA_LINK_H
#define DNAI_MODELS_GUI_DATA_LINK_H

#include "dnai/models/gui/instruction.h"
#include "dnai/models/gui/declarable/variable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Link
				{
					gui::Instruction *instruction;
					declarable::Variable *variable;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_LINK_H