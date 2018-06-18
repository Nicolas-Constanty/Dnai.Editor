#include "dnai/models/gui/data/entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            namespace data {
                bool Entity::operator!=(const Entity& other) const
                {
                    return !(*this == other);
                }

                bool Entity::operator==(const Entity& other) const
                {
                    return (index == other.index && listIndex == other.listIndex && description == other.description && expanded == other.expanded);
                }
            }
		}
	}
}
