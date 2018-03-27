#ifndef DNAI_MODELS_INSTRUCTION_H
#define DNAI_MODELS_INSTRUCTION_H

#include "core/entity.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		class Instruction : public Entity
		{
		public:
			~Instruction() = default;

            core::Entity* coreModel() const override;
            void setCoreModel(core::Entity* model) override;
        private:
            core::Entity * m_data = nullptr;
		};
	}
}

#endif //DNAI_MODELS_INSTRUCTION_H
