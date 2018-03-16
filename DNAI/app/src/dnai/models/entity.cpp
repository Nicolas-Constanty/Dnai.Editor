#include <QJsonArray>
#include "dnai/models/entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/context.h"

namespace dnai
{
	namespace models
	{
        Entity::Entity() : IModel(nullptr), m_dataCore(nullptr), m_dataGUI(nullptr)
        {
        }

		Entity::Entity(core::Entity* coremodel, interfaces::IEntity* guimodel, GenericTreeItem * parent) : IModel(parent), m_dataCore(coremodel), m_dataGUI(guimodel)
        {
        }

        Entity::Entity(core::Entity *coremodel, GenericTreeItem *parent, interfaces::IEntity *guimodel) : IModel(parent), m_dataCore(coremodel), m_dataGUI(guimodel)
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

		void Entity::declare()
		{
			m_dataCore->declare();
		}

		void Entity::setId(qint32 id)
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
				
				emit Entity::visibilityChanged(v);
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
            switch (m_dataCore->entityType())
            {
            case enums::UNDEFINED: break;
            case enums::CONTEXT:
            {
                const auto ctx = dynamic_cast<gui::declarable::Context *>(m_dataGUI);
                ctx->serialize(obj);
                break;
            }
            case enums::VARIABLE:
            {
                const auto var = dynamic_cast<gui::declarable::Variable *>(m_dataGUI);
                var->serialize(obj);
                break;
            }
            case enums::FUNCTION:
            {
                const auto func = dynamic_cast<gui::declarable::Function *>(m_dataGUI);
                func->serialize(obj);
                break;
            }
            case enums::DATA_TYPE: break;
            case enums::ENUM_TYPE: break;
            case enums::OBJECT_TYPE:
            {
                const auto classe = dynamic_cast<gui::declarable::ObjectType *>(m_dataGUI);
                classe->serialize(obj);
                break;
            }
            case enums::LIST_TYPE: break;
            default: ;
            }
			for (auto child : children())
			{
				const auto entity = dynamic_cast<Entity *>(child);
				entity->serialize(obj);
			}
		}

		void Entity::_deserialize(const QJsonObject& obj)
		{
			m_dataCore->setName(obj["name"].toString());
            m_dataCore->setVisibility(static_cast<enums::core::VISIBILITY>(obj["visibility"].toInt()));
            switch (m_dataCore->entityType())
            {
            case enums::UNDEFINED: break;
            case enums::CONTEXT:
            {
                m_dataGUI = gui::declarable::Context::deserialize(obj);
                break;
            }
            case enums::VARIABLE:
            {
                m_dataGUI = gui::declarable::Variable::deserialize(obj);
                break;
            }
            case enums::FUNCTION:
            {
                m_dataGUI = gui::declarable::Function::deserialize(obj);
                break;
            }
            case enums::DATA_TYPE: break;
            case enums::ENUM_TYPE:
                m_dataGUI = gui::declarable::EnumType::deserialize(obj);
                break;
            case enums::OBJECT_TYPE:
            {
                m_dataGUI = gui::declarable::ObjectType::deserialize(obj);
                break;
            }
            case enums::LIST_TYPE:
                m_dataGUI = gui::declarable::ListType::deserialize(obj);
                break;
            default: ;
            }

            foreach(const auto classe, obj["classes"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::OBJECT_TYPE);
				GenericTreeItem *parent = this;
                const auto entity = Entity::deserialize(classe.toObject(), coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto context, obj["contexts"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::CONTEXT);
				GenericTreeItem *parent = this;
                const auto entity = deserialize(context.toObject(), coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto variable, obj["variables"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::VARIABLE);
				GenericTreeItem *parent = this;
                const auto entity = Entity::deserialize(variable.toObject(),coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto function, obj["functions"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::FUNCTION);
				GenericTreeItem *parent = this;
                const auto entity = Entity::deserialize(function.toObject(), coreModel, parent);
				appendChild(entity);
			}
		}

		int Entity::columnCount() const
		{
			return 1;
		}
	}
}
