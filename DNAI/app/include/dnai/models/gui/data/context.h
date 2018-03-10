#ifndef DNAI_MODELS_GUI_DATA_CONTEXT_H
#define DNAI_MODELS_GUI_DATA_CONTEXT_H

#include "entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/function.h"
#include "dnai/models/gui/declarable/objecttype.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Context : Entity
				{
					QList<Context*> contexts;
					QList<declarable::ObjectType*> classes;
					QList<declarable::Variable*> variables;
					QList<declarable::Function*> functions;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_CONTEXT_H