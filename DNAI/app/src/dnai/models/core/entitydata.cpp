#include "dnai/models/core/entitydata.h"

namespace dnai
{
	namespace models
	{
		namespace core
		{
			EntityData::EntityData(const EntityData& other)
			{
				*this = other;
			}

			EntityData& EntityData::operator=(const EntityData& other)
			{
				id = other.id;
				containerId = other.containerId;
				type = other.type;
				name = other.name;
				visibility = other.visibility;
				return *this;
			}

			bool EntityData::operator!=(const EntityData& other) const
			{
				return !(*this == other);
			}

			bool EntityData::operator==(const EntityData& other) const
			{
				return (type == other.type && containerId == other.containerId && name == other.name && visibility == other.visibility);
			}
		}
	}
}