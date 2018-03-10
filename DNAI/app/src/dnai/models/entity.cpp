#include <QJsonObject>
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		Entity::Entity() : m_dataCore(nullptr), m_dataGUI(nullptr)
		{
		}

		Entity::Entity(core::Entity *model, const QString &description) : m_dataCore(model), m_dataGUI(nullptr)
		{
			m_dataGUI->setDescription(description);
		}

		Entity::Entity(core::Entity* coremodel, gui::declarable::Entity* guimodel): m_dataCore(coremodel), m_dataGUI(guimodel)
		{
		}

		qint32 Entity::id() const
		{
			return coreModel()->id();
		}

        qint32 Entity::containerId() const
		{
			return coreModel()->containerId();
		}

		enums::core::ENTITY Entity::entityType() const
		{
			return coreModel()->entityType();
		}

		const QString& Entity::name() const
		{
			if (coreModel()->entityType() == enums::core::ENTITY::UNDEFINED)
				return "default";
			return coreModel()->name();
		}

		enums::core::VISIBILITY Entity::visibility() const
		{
			return coreModel()->visibility();
		}

		int Entity::index() const
		{
			return m_dataGUI->index();
		}

		int Entity::listIndex() const
		{
			return m_dataGUI->listIndex();
		}

		const QString& Entity::description() const
		{
			return m_dataGUI->description();
		}

		core::Entity* Entity::coreModel() const
		{
			return m_dataCore;
		}

        interfaces::IEntity *Entity::guiModel() const
        {
            return m_dataGUI;
        }

        void Entity::setId(qint32 id) const
		{
			if (coreModel()->setId(id))
			{
				emit idChanged(id);
			}
		}

        void Entity::setContainerId(qint32 containerId) const
		{
			if (coreModel()->setContainerId(containerId))
			{
				emit containerIdChanged(containerId);
			}
		}

		void Entity::setEntityType(enums::core::ENTITY type) const
		{
			if (coreModel()->setEntityType(type))
			{
				emit entityTypeChanged(type);
			}
		}

		void Entity::setName(const QString& name) const
		{
			if (coreModel()->setName(name))
			{
				emit nameChanged(name);
			}
		}

		void Entity::setVisibility(enums::core::VISIBILITY v) const
		{
			if (coreModel()->setVisibility(v))
			{
				emit visibilityChanged(v);
			}
		}

		void Entity::setIndex(int index)
		{
			if (m_dataGUI->setIndex(index))
			{
				emit indexChanged(index);
			}
		}

		void Entity::setListIndex(int listIndex)
		{
			if (m_dataGUI->setListIndex(listIndex))
			{
				emit listIndexChanged(listIndex);
			}
		}

		void Entity::setDescription(const QString& description)
		{
			if (m_dataGUI->setDescription(description))
			{
				emit descriptionChanged(description);
			}
		}

		void Entity::setCoreModel(core::Entity* model)
		{
			if (m_dataCore == model)
				return;
			m_dataCore = model;
			emit coreModelChanged(model);
		}

		void Entity::serialize(QJsonObject& obj) const
		{
			if (m_dataCore == nullptr) return;
			obj["name"] = m_dataCore->name();
			obj["descrition"] = m_dataGUI->description();
			obj["uid"] = m_dataCore->id();
			obj["containerId"] = m_dataCore->containerId();
			switch (m_dataCore->entityType())
			{
			case enums::UNDEFINED: break;
			case enums::CONTEXT: break;
			case enums::VARIABLE: break;
			case enums::FUNCTION: break;
			case enums::DATA_TYPE: break;
			case enums::ENUM_TYPE: break;
			case enums::OBJECT_TYPE: break;
			case enums::LIST_TYPE: break;
			default: ;
			}
		}

		void Entity::_deserialize(const QJsonObject& obj)
		{
		}
	}
}
