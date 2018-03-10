#ifndef DNAI_MODELS_GUI_DATA_VARIABLE_H
#define DNAI_MODELS_GUI_DATA_VARIABLE_H

#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Variable : Entity
				{
					quint32 varType;
					QJsonObject value;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_VARIABLE_H