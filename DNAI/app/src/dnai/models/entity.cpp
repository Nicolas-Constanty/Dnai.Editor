#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		Entity::Entity() : m_dataCore(nullptr)
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
			return m_dataGUI.index();
		}

		int Entity::listIndex() const
		{
			return m_dataGUI.listIndex();
		}

		const QString& Entity::description() const
		{
			return m_dataGUI.description();
		}

		EntityCore* Entity::coreModel() const
		{
			return m_dataCore;
		}

//		const EntityGUI* Entity::guiModel() const
//		{
//			return &m_dataGUI;
//		}

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
			if (m_dataGUI.setIndex(index))
			{
				emit indexChanged(index);
			}
		}

		void Entity::setListIndex(int listIndex)
		{
			if (m_dataGUI.setListIndex(listIndex))
			{
				emit listIndexChanged(listIndex);
			}
		}

		void Entity::setDescription(const QString& description)
		{
			if (m_dataGUI.setDescription(description))
			{
				emit descriptionChanged(description);
			}
		}

		void Entity::setCoreModel(EntityCore* model)
		{
			if (m_dataCore == model)
				return;
			m_dataCore = model;
			emit coreModelChanged(model);
		}
	}
}
