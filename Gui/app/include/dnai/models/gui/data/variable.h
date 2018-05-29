#ifndef DNAI_MODELS_GUI_DATA_VARIABLE_H
#define DNAI_MODELS_GUI_DATA_VARIABLE_H

#include <QJsonObject>
#include "entity.h"
#include "core.h"
#include <QVariantList>

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
                    ::core::EntityID varType = 2;
					QString value = "100";
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_VARIABLE_H
