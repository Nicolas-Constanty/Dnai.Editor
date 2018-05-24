#ifndef DNAI_MODELS_GUI_DATA_VARIABLE_H
#define DNAI_MODELS_GUI_DATA_VARIABLE_H

#include <QJsonObject>
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
                    ::core::EntityID varType = ::core::UNDEFINED_ID;
					QJsonObject value;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_VARIABLE_H
