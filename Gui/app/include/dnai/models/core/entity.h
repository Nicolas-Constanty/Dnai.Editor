#ifndef DNAI_MODELS_CORE_ENTITY_H
#define DNAI_MODELS_CORE_ENTITY_H

#include <QDebug>
#include "core.h"
#include "entitydata.h"
#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"

namespace dnai
{
	namespace models
	{
        namespace gcore
		{
			class IEntityCore
			{
			public:
				virtual ~IEntityCore() = default;
                virtual void replicate() const = 0;
			};

			class Entity : public IEntityCore, public interfaces::IModelData<EntityData>, public interfaces::ASerializable<Entity>
			{
			public:
                Entity(::core::ENTITY type = ::core::ENTITY::UNDEFINED);
				Entity(const Entity &entity);
                explicit Entity(const QString& name, ::core::ENTITY type = ::core::ENTITY::UNDEFINED, qint32 ctId = -1);
                explicit Entity(qint32 id, const QString& name, ::core::ENTITY type = ::core::ENTITY::UNDEFINED, qint32 ctId = -1);
				virtual ~Entity();

				bool setId(qint32 id);
				qint32 id() const;

                bool setEntityType(::core::ENTITY e);
                ::core::ENTITY entityType() const;

				bool setContainerId(qint32 c);
				qint32 containerId() const;

				bool setName(const QString &d);
				const QString &name() const;

                bool setVisibility(::core::VISIBILITY v);
                ::core::VISIBILITY visibility() const;

				Entity& operator=(const Entity& other);

            public:
                //will replicate the current entity into the CoreDaemon
                virtual void replicate() const override;

				// IModelData implementation
			public:
				bool setData(const EntityData &d) override;
				const EntityData &data() const override;

				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			private:
                EntityData m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_CORE_ENTITY_H
