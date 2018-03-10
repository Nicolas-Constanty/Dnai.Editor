#ifndef DNAI_MODELS_GUI_DATA_ENTITY_H
#define DNAI_MODELS_GUI_DATA_ENTITY_H

#include <QString>

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
					int listIndex = -1;
					QString description;

					Entity& operator=(const Entity& other) = default;
					bool operator!=(const Entity& other) const;
					bool operator==(const Entity& other) const;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_ENTITY_H