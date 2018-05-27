#ifndef DNAI_MODELS_GUI_DATA_ENUMTYPE_H
#define DNAI_MODELS_GUI_DATA_ENUMTYPE_H
#include <QJsonArray>
#include <QMap>
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct EnumType : Entity
				{
					QStringList values;
					EnumType& operator=(const EnumType& other) = default;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_ENUMTYPE_H