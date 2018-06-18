#ifndef DNAI_MODELS_GUI_DATA_INSTRUCTION_H
#define DNAI_MODELS_GUI_DATA_INSTRUCTION_H

#include <QList>
#include "dnai/enums/core/instructionid.h"
#include "dnai/models/gui/flow.h"
#include "dnai/models/gui/input.h"
#include "dnai/models/gui/output.h"
#include "dnai/models/gui/iolink.h"

namespace dnai
{
	namespace models
	{
		class Entity;

		namespace gui
		{
			namespace data
			{
				struct Instruction
				{
					quint32 uid;
					QUuid guiUuid;
                    QList<models::gui::Input*> inputs;
					QList<models::gui::Output*> outputs;
                    gui::Flow* flowIn = nullptr;
                    QList<gui::Flow*> flowOut;
					qint32 instructionId = enums::QInstructionID::Instruction_ID::UNDEFINED;
                    QList<QString> linked;
                    QString nodeMenuPath; //path of the ContextMenuItem in the ContextMenuModel : ex : "/operators/binary/int/add"

					Instruction& operator=(const Instruction& other) = default;
					qint32 x = 0;
					qint32 y = 0;

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
							&& instructionId == other.instructionId
							&& guiUuid == other.guiUuid);
                    }
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_INSTRUCTION_H
