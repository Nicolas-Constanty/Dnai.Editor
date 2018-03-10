#ifndef DNAI_MODELS_INSTRUCTION_H
#define DNAI_MODELS_INSTRUCTION_H

#include "core/entity.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
        class InstructionCore : public core::Entity
		{
		public:
            std::map<qint32, commands::CoreCommand*> initCommands() const override;
		};

        class MemberInstructionCore : public core::Entity
		{
		public:
            std::map<qint32, commands::CoreCommand*> initCommands() const override;
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

            core::Entity* coreModel() const override;
            void setCoreModel(core::Entity* model) override;
		private:
			InstructionCoreUnion m_dataCore;
            core::Entity * m_data = nullptr;
		};
	}
}

#endif //DNAI_MODELS_INSTRUCTION_H
