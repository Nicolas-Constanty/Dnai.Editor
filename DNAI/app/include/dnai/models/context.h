#ifndef DNAI_MODEL_CONTEXT_H
#define DNAI_MODEL_CONTEXT_H

//#include "dnai/models/common.h"
//#include "dnai/models/position.h"
#include "entity.h"
#include "dnai/models/gui/declarable/context.h"

namespace dnai {
	namespace models {
		class Context : public Entity
		{
		public:
			gui::declarable::Context *guiModel() const override
			{
				return dynamic_cast<gui::declarable::Context *>(Entity::guiModel());
			}
		};
	}
}

#endif // DNAI_MODEL_CONTEXT_H
