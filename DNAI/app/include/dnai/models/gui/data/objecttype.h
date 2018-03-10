#ifndef DNAI_MODELS_GUI_DATA_OBJECTTYPE_H
#define DNAI_MODELS_GUI_DATA_OBJECTTYPE_H

#include "entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/function.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable {
				class ObjectType;
			}
			namespace data
			{
				struct ObjectType : Entity
				{
					QList<declarable::Variable*> attributes;
					QList<declarable::Function*> methods;
					QList<declarable::Function*> functions;
					QList<declarable::ObjectType*> classes;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_OBJECTTYPE_H