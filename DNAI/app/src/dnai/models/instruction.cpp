#include <QDebug>
#include "dnai/models/instruction.h"

namespace dnai
{
	namespace models
	{
        std::map<qint32, commands::EntityCommand*> InstructionCore::initCommands() const
		{
            return core::Entity::initCommands();
		}

        std::map<qint32, commands::EntityCommand*> MemberInstructionCore::initCommands() const
		{
            return core::Entity::initCommands();
		}

        core::Entity* Instruction::coreModel() const
		{
			return m_data;
		}

        void Instruction::setCoreModel(core::Entity* model)
		{
			if (model->entityType() == enums::core::ENTITY::DATA_TYPE)
			{
                if (model->id() == -1)
				{
					m_data = &m_dataCore.i;
				}
				else
				{
					m_data = &m_dataCore.mi;
				}
			}
			else
				qDebug() << "BAD TYPE";
		}
	}
}
