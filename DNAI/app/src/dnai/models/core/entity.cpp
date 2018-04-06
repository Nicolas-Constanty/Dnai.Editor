#include "dnai/models/core/entity.h"
#include "dnai/commands/commandmanager.h"

namespace dnai
{
	namespace models
	{
		namespace core
        {
            Entity::Entity(enums::core::ENTITY type)
			{
				m_data.name = "EmptyEntity";
                m_data.containerId = 0;
                m_data.type = type;
			}

			Entity::Entity(const Entity& entity)
			{
				*this = entity;
			}

			Entity::Entity(const QString& name, enums::core::ENTITY type, qint32 ctId)
			{
				m_data.name = name;
				m_data.type = type;
				m_data.containerId = ctId;
			}

			Entity::Entity(qint32 id, const QString& name, enums::core::ENTITY type, qint32 ctId)
			{
				m_data.id = id;
				m_data.name = name;
				m_data.type = type;
				m_data.containerId = ctId;
			}

			Entity::~Entity()
			{

			}

			bool Entity::setId(qint32 id)
			{
				if (m_data.id == id)
					return false;
				m_data.id = id;
				return true;
			}

			qint32 Entity::id() const
			{
				return m_data.id;
			}

			bool Entity::setData(const EntityData& d)
			{
				if (d == m_data)
					return false;
				m_data = d;
				return true;
			}

			const EntityData& Entity::data() const
			{
				return m_data;
			}

			void Entity::serialize(QJsonObject& obj) const
			{
				obj["name"] = m_data.name;
				obj["type"] = m_data.type;
				obj["visibility"] = m_data.visibility;
			}

			void Entity::_deserialize(const QJsonObject& obj)
			{
                m_data.name = obj["name"].toString();
                m_data.type = static_cast<enums::core::ENTITY>(obj["type"].toInt());
                m_data.visibility = static_cast<enums::core::VISIBILITY>(obj["visibility"].toInt());
			}

			bool Entity::setEntityType(enums::core::ENTITY e)
			{
				if (m_data.type == e)
					return false;
				m_data.type = e;
				return true;
			}

			enums::core::ENTITY Entity::entityType() const
			{
				return m_data.type;
			}

			bool Entity::setContainerId(const qint32 c)
			{
				if (m_data.containerId == c)
					return false;
				m_data.containerId = c;
				return true;
			}

			qint32 Entity::containerId() const
			{
				return m_data.containerId;
			}

			bool Entity::setName(const QString& d)
			{
				if (m_data.name == d)
					return false;
				m_data.name = d;
				return true;
			}

			const QString& Entity::name() const
			{
				return m_data.name;
			}

			bool Entity::setVisibility(enums::core::VISIBILITY v)
			{
				if (m_data.visibility == v)
					return false;
				m_data.visibility = v;
				return true;
			}

			enums::core::VISIBILITY Entity::visibility() const
			{
				return m_data.visibility;
			}

			Entity& Entity::operator=(const Entity& other)
			{
				m_data = other.data();
				return *this;
            }

            void Entity::replicate() const
            {
                //declare();
            }
		}
	}
}
