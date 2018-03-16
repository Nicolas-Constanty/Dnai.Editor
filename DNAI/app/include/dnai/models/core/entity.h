#ifndef DNAI_MODELS_CORE_ENTITY_H
#define DNAI_MODELS_CORE_ENTITY_H

#include <QDebug>
#include "dnai/enums/core/core.h"
#include "dnai/commands/corecommand.h"
#include "entitydata.h"
#include "dnai/interfaces/imodeldata.h"

namespace dnai
{
	namespace models
	{
		namespace core
		{
			class IEntityCore
			{
			public:
				virtual ~IEntityCore() = default;
				virtual void callCoreCommand(enums::core::COMMANDS cmd) const = 0;
                virtual const std::map<qint32, commands::CoreCommand*> &commands() const = 0;
			};

			class Entity : public IEntityCore, public interfaces::IModelData<EntityData>
			{
			public:
                Entity(enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED);
				Entity(const Entity &entity);
				explicit Entity(const QString& name, enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED, qint32 ctId = -1);
				explicit Entity(qint32 id, const QString& name, enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED, qint32 ctId = -1);
				virtual ~Entity();

				bool setId(qint32 id);
				qint32 id() const;

				bool setEntityType(enums::core::ENTITY e);
				enums::core::ENTITY entityType() const;

				bool setContainerId(qint32 c);
				qint32 containerId() const;

				bool setName(const QString &d);
				const QString &name() const;

				bool setVisibility(enums::core::VISIBILITY v);
				enums::core::VISIBILITY visibility() const;

				void declare()
				{
					qDebug() << m_data.name;
				};

				Entity& operator=(const Entity& other);

				//IEntityCore implementation
			public:
				void callCoreCommand(enums::core::COMMANDS cmd) const override;
				const std::map<qint32, commands::CoreCommand*> &commands() const override;

				// IModelData implementation
			public:
				bool setData(const EntityData &d) override;
				const EntityData &data() const override;

			private:
				EntityData m_data;
				static std::map<qint32, commands::CoreCommand*> m_commands;

			};
		}
	}
}

#endif //DNAI_MODELS_CORE_ENTITY_H
