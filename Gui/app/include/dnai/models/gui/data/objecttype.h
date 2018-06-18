#ifndef DNAI_MODELS_GUI_DATA_OBJECTTYPE_H
#define DNAI_MODELS_GUI_DATA_OBJECTTYPE_H

#include "entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/function.h"
#include "dnai/models/gui/declarable/enumtype.h"
#include "dnai/models/gui/declarable/listtype.h"

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
                    QMap<QString, quint32> attributes;
                    QMap<QString, bool> functions;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_OBJECTTYPE_H
