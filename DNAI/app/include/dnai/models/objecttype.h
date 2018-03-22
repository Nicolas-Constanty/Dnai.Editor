#ifndef DNAI_MODEL_OBJECTTYPE_H
#define DNAI_MODEL_OBJECTTYPE_H

//#include "dnai/models/common.h"
//#include "dnai/models/position.h"
#include "entity.h"
#include "dnai/models/gui/declarable/objecttype.h"

namespace dnai {
	namespace models {
		class ObjectType : public Entity
		{
		public:
			gui::declarable::ObjectType *guiModel() const override
			{
				return dynamic_cast<gui::declarable::ObjectType *>(Entity::guiModel());
			}
		};
	}
}

#endif // DNAI_MODEL_OBJECTTYPE_H
