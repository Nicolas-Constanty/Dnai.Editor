#ifndef DNAI_MODELS_CORE_ENTITYDATA_H
#define DNAI_MODELS_CORE_ENTITYDATA_H

#include <QString>
#include "dnai/enums/core/core.h"

namespace dnai
{
	namespace models
	{
		namespace core
		{
			struct EntityData
			{
				EntityData() = default;
				EntityData(const EntityData& other);
				virtual ~EntityData() = default;

				EntityData& operator=(const EntityData& other);
				bool operator!=(const EntityData& other) const;
				bool operator==(const EntityData& other) const;

                enums::core::EntityID id = 0;
                enums::core::EntityID containerId = 0;
				enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED;
				QString name;
				enums::core::VISIBILITY visibility = enums::core::VISIBILITY::PRIVATE;
			};
		}
	}
}

#endif //DNAI_MODELS_CORE_ENTITYDATA_H
