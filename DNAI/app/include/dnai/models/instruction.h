#ifndef DNAI_MODELS_INSTRUCTION_H
#define DNAI_MODELS_INSTRUCTION_H

#include "entitycore.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		class InstructionCore : public EntityCore
		{
		public:
			std::map<qint32, commands::EntityCommand*> initCommands() const override;
		};

		class MemberInstructionCore : public EntityCore
		{
		public:
			std::map<qint32, commands::EntityCommand*> initCommands() const override;
		};

		union InstructionCoreUnion
		{
			InstructionCore i;
			MemberInstructionCore mi;
			~InstructionCoreUnion() {}
		};
		class Instruction : public Entity
		{
		public:
			~Instruction() = default;

			EntityCore* coreModel() const override;
			void setCoreModel(EntityCore* model) override;
		private:
			InstructionCoreUnion m_dataCore;
			EntityCore * m_data = nullptr;
		};
	}
}

#endif //DNAI_MODELS_INSTRUCTION_H