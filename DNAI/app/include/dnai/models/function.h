#ifndef DNAI_MODEL_FUNCTION_H
#define DNAI_MODEL_FUNCTION_H

//#include "dnai/models/common.h"
//#include "dnai/models/position.h"
#include "entity.h"
#include "dnai/models/gui/declarable/function.h"

namespace dnai {
	namespace models {
		class Function : public Entity
		{
		public:
			gui::declarable::Function *guiModel() const override
			{
				return dynamic_cast<gui::declarable::Function *>(Entity::guiModel());
			}
		};
	}
}

#endif // DNAI_MODEL_FUNCTION_H
