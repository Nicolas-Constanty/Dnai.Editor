#include "dnai/models/entitycore.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
	namespace models
	{
		EntityCoreData::EntityCoreData(const EntityCoreData& other)
		{
			*this = other;
		}

		EntityCoreData& EntityCoreData::operator=(const EntityCoreData& other)
		{
			id = other.id;
			containerId = other.containerId;
			type = other.type;
			name = other.name;
			visibility = other.visibility;
			return *this;
		}

		bool EntityCoreData::operator!=(const EntityCoreData& other) const
		{
			return !(*this == other);
		}

		bool EntityCoreData::operator==(const EntityCoreData& other) const
		{
			return (type == other.type && containerId == other.containerId && name == other.name && visibility == other.visibility);
		}

		EntityCore::EntityCore()
		{
			m_data.name = "EmptyEntity";
			m_data.containerId = -1;
			m_data.type = enums::core::ENTITY::UNDEFINED;
		}

		EntityCore::EntityCore(const EntityCore& entity)
		{
			*this = entity;
		}

		EntityCore::EntityCore(const QString& name, enums::core::ENTITY type, qint32 ctId)
		{
			m_data.name = name;
			m_data.type = type;
			m_data.containerId = ctId;
		}

		EntityCore::EntityCore(qint32 id, const QString& name, enums::core::ENTITY type, qint32 ctId)
		{
			m_data.id = id;
			m_data.name = name;
			m_data.type = type;
			m_data.containerId = ctId;
		}

		EntityCore::~EntityCore()
		{
		}

		bool EntityCore::setId(qint32 id)
		{
			if (m_data.id == id)
				return false;
			m_data.id = id;
			return true;
		}

		qint32 EntityCore::id() const
		{
			return m_data.id;
		}

		bool EntityCore::setData(const EntityCoreData& d)
		{
			if (d == m_data)
				return false;
			m_data = d;
			return true;
		}

		const EntityCoreData& EntityCore::data() const
		{
			return m_data;
		}

		bool EntityCore::setEntityType(enums::core::ENTITY e)
		{
			if (m_data.type == e)
				return false;
			m_data.type = e;
			return true;
		}

		enums::core::ENTITY EntityCore::entityType() const
		{
			return m_data.type;
		}

		bool EntityCore::setContainerId(const qint32 c)
		{
			if (m_data.containerId == c)
				return false;
			m_data.containerId = c;
			return true;
		}

		qint32 EntityCore::containerId() const
		{
			return m_data.containerId;
		}

		bool EntityCore::setName(const QString& d)
		{
			if (m_data.name == d)
				return false;
			m_data.name = d;
			return true;
		}

		const QString& EntityCore::name() const
		{
			return m_data.name;
		}

		bool EntityCore::setVisibility(enums::core::VISIBILITY v)
		{
			if (m_data.visibility == v)
				return false;
			m_data.visibility = v;
			return true;
		}

		enums::core::VISIBILITY EntityCore::visibility() const
		{
			return m_data.visibility;
		}

		EntityCore& EntityCore::operator=(const EntityCore& other)
		{
			m_data = other.data();
			return *this;
		}

		void EntityCore::callCoreCommand(const enums::core::COMMANDS cmd) const
		{
			if (m_commands.find(cmd) != m_commands.end())
			{
				commands::CommandManager::Instance()->exec(m_commands.at(cmd));
			}
		}

		std::map<qint32, commands::EntityCommand*> EntityCore::initCommands() const
		{
			std::map<qint32, commands::EntityCommand*> map;
			map[enums::core::DECLARE] = new commands::EntityCommand();
			map[enums::core::REMOVE] = new commands::EntityCommand();
			map[enums::core::RENAME] = new commands::EntityCommand();
			map[enums::core::MOVE] = new commands::EntityCommand();
			map[enums::core::CHANGE_VISIBILITY] = new commands::EntityCommand();
			return map;
		}
	}
}
