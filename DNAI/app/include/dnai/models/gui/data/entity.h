#ifndef DNAI_MODELS_GUI_DATA_ENTITY_H
#define DNAI_MODELS_GUI_DATA_ENTITY_H

#include <QString>
#include <QUuid>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct Entity
				{
					int index = -1;
					QUuid listIndex;
					QString description;
					bool expanded = false;

					Entity& operator=(const Entity& other) = default;
					bool operator!=(const Entity& other) const;
					bool operator==(const Entity& other) const;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_ENTITY_H