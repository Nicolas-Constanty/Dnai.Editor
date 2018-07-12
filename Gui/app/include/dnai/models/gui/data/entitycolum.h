#ifndef DNAI_MODELS_GUI_DATA_ENTITYCOLUMN_H
#define DNAI_MODELS_GUI_DATA_ENTITYCOLUMN_H

#include <QString>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace data
			{
				struct EntityColumn
				{
					QUuid listIndex;
					QString name;
					QString description;

					EntityColumn& operator=(const EntityColumn& other) = default;
					bool operator!=(const EntityColumn& other) const;
					bool operator==(const EntityColumn& other) const;
				};

				inline bool EntityColumn::operator!=(const EntityColumn& other) const
				{
                    return (other == *this);
				}

				inline bool EntityColumn::operator==(const EntityColumn& other) const
				{
					return (listIndex == other.listIndex && name == other.name && description == other.description);
				}
			}
		}
	}
}

#endif //DNAI_MODELS_GUI_DATA_ENTITYCOLUMN_H
