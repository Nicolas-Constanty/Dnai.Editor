#ifndef DNAI_MODEL_VARIABLE_H
#define DNAI_MODEL_VARIABLE_H

//#include "dnai/models/common.h"
//#include "dnai/models/position.h"
#include "entity.h"
#include "dnai/models/gui/declarable/variable.h"

namespace dnai {
	namespace models {
		class Variable : public Entity
		{
		public:
			gui::declarable::Variable *guiModel() const override
			{
				return dynamic_cast<gui::declarable::Variable *>(Entity::guiModel());
			}
		};
	}
}

#endif // DNAI_MODEL_VARIABLE_H
