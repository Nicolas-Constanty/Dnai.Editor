#ifndef DNAI_MODELS_GUI_DATA_VARIABLE_H
#define DNAI_MODELS_GUI_DATA_VARIABLE_H

#include "entity.h"
#include "core.h"

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
                    QUuid varType = "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}"; //int type
                    QString value = "";
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_VARIABLE_H
