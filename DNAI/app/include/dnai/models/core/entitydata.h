#ifndef DNAI_MODELS_CORE_ENTITYDATA_H
#define DNAI_MODELS_CORE_ENTITYDATA_H

#include <QString>
#include "core.h"
namespace dnai
{
	namespace models
	{
        namespace gcore
		{
			struct EntityData
			{
				EntityData() = default;
				EntityData(const EntityData& other);
				virtual ~EntityData() = default;

				EntityData& operator=(const EntityData& other);
				bool operator!=(const EntityData& other) const;
				bool operator==(const EntityData& other) const;

                ::core::EntityID id = ::core::UNDEFINED_ID;
                ::core::EntityID containerId = ::core::UNDEFINED_ID;
                ::core::ENTITY type = ::core::ENTITY::UNDEFINED;
                QString name = "Undefined";
                ::core::VISIBILITY visibility = ::core::VISIBILITY::PRIVATE;
			};
		}
	}
}

#endif //DNAI_MODELS_CORE_ENTITYDATA_H
