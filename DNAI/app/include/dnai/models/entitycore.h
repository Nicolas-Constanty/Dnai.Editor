#ifndef ENTITYCORE
#define ENTITYCORE

#include "ientity.h"
#include "dnai/enums/core/core.h"
#include "dnai/commands/entitycommand.h"

namespace dnai
{
	namespace models
	{
		struct EntityCoreData
		{
			EntityCoreData() = default;
			EntityCoreData(const EntityCoreData& other);
			virtual ~EntityCoreData() = default;

			EntityCoreData& operator=(const EntityCoreData& other);
			bool operator!=(const EntityCoreData& other) const;
			bool operator==(const EntityCoreData& other) const;

			qint32 id = -1;
			qint32 containerId = -1;
			enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED;
			QString name;
			enums::core::VISIBILITY visibility = enums::core::VISIBILITY::PRIVATE;
		};

		class IEntityCore
		{
		public:
			virtual ~IEntityCore() = default;
			virtual void callCoreCommand(enums::core::COMMANDS cmd) const = 0;
			virtual std::map<qint32, commands::EntityCommand *> initCommands() const = 0;

		protected:
			std::map<qint32, commands::EntityCommand *> m_commands;
		};

		class EntityCore : public IEntityCore, public IEntity<EntityCoreData>
		{
		public:
			EntityCore();
			EntityCore(const EntityCore &entity);
			explicit EntityCore(const QString& name, enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED, qint32 ctId = -1);
			explicit EntityCore(qint32 id, const QString& name, enums::core::ENTITY type = enums::core::ENTITY::UNDEFINED, qint32 ctId = -1);
			virtual ~EntityCore();

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

			EntityCore& operator=(const EntityCore& other);

		//IEntityCore implementation
		public:
			void callCoreCommand(enums::core::COMMANDS cmd) const override;
			std::map<qint32, commands::EntityCommand*> initCommands() const override;

			// IEntity implementation
		public:
			bool setData(const EntityCoreData &d) override;
			const EntityCoreData &data() const override;
		private:
			EntityCoreData m_data;

		};
	}
}

#endif
