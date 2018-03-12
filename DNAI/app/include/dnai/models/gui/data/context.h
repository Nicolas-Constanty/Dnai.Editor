#ifndef DNAI_MODELS_GUI_DATA_CONTEXT_H
#define DNAI_MODELS_GUI_DATA_CONTEXT_H

#include "entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/function.h"
#include "dnai/models/gui/declarable/objecttype.h"
#include "dnai/models/gui/declarable/enumtype.h"
#include "dnai/models/gui/declarable/listtype.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class Context;
			}
			namespace data
			{
				struct Context : Entity
				{
					QList<declarable::Context*> contexts;
					QList<declarable::ObjectType*> classes;
					QList<declarable::Variable*> variables;
					QList<declarable::Function*> functions;
					QList<declarable::EnumType*> enums;
					QList<declarable::ListType*> listobjs;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_CONTEXT_H