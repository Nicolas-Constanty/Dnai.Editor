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

        Entity::Entity(core::Entity *coremodel, Entity *parent, interfaces::IEntity *guimodel) : IModel(parent), m_dataCore(coremodel), m_dataGUI(guimodel)
        {

        }

		Entity::~Entity()
		{
			delete m_dataCore;
			delete m_dataGUI;
		}

		bool Entity::isRoot() const
		{
			return m_isRoot;
		}

		void Entity::setIsRoot(bool isRoot)
		{
			if (m_isRoot == isRoot)
				return;
			m_isRoot = isRoot;
			emit isRootChanged(isRoot);
		}

		qint32 Entity::id() const
		{
			return coreModel()->id();
		}

        qint32 Entity::containerId() const
		{
			return coreModel()->containerId();
		}

		qint32 Entity::entityType() const
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

		const QString &Entity::listIndex() const
		{
			return m_dataGUI->listIndex().toString();
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

		bool Entity::expanded() const
		{
			return m_dataGUI->expanded();
		}

		void Entity::setExpanded(bool exp)
		{
			if (guiModel()->setExpanded(exp))
			{
				emit expandedChanged(exp);
			}
		}

		void Entity::declare()
		{
			m_dataCore->declare();
		}

		Entity* Entity::parentRef() const
		{
			return parentItem();
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

		void Entity::setEntityType(qint32 type) const
		{
			if (coreModel()->setEntityType(static_cast<enums::ENTITY>(type)))
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

		void Entity::setListIndex(const QString &listIndex)
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

		void Entity::appendChild(Entity* child)
		{
			GenericTreeItem<Entity>::appendChild(child);
			const auto uuid = QUuid(child->guiModel()->listIndex());
			if (m_columns.find(uuid) == m_columns.end())
			{
				const auto c = new Column();
				m_columslist.append(c);
				m_columns[uuid] = c;
			}
			m_columns[uuid]->append(child);
			emit entityChildrenChanged(child);
		}

		void Entity::serialize(QJsonObject& obj) const
		{
			QJsonArray arr;
			for (auto c : m_columns)
			{
				QJsonObject tmp;
				c->serialize(tmp);
				arr.append(tmp);
			}
			obj["columns"] = arr;
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
            case enums::LIST_TYPE: 
            	break;
            default: ;
            }
            for (auto child : childrenItem())
			{
				const auto entity = dynamic_cast<Entity *>(child);
				entity->serialize(obj);
			}
		}

		void Entity::_deserialize(const QJsonObject& obj)
		{
			foreach(const auto column, obj["columns"].toArray()) {
				qDebug() << "Column";
				const auto col = Column::deserialize(obj);
                m_columns[col->datas().listIndex] = col;
				m_columslist.append(col);
			}
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
                Entity *parent = this;
                const auto entity = Entity::deserialize(classe.toObject(), coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto context, obj["contexts"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::CONTEXT);
                Entity *parent = this;
                const auto entity = deserialize(context.toObject(), coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto variable, obj["variables"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::VARIABLE);
                Entity *parent = this;
                const auto entity = Entity::deserialize(variable.toObject(),coreModel, parent);
				appendChild(entity);
			}

            foreach(const auto function, obj["functions"].toArray()) {
                const auto coreModel = new models::core::Entity(enums::core::FUNCTION);
                Entity *parent = this;
                const auto entity = Entity::deserialize(function.toObject(), coreModel, parent);
				appendChild(entity);
			}
		}

		void Entity::addContext(const int index, const QString &listindex)
		{
			const auto coreModel = new models::core::Entity(enums::core::CONTEXT);
			const auto guiModel = new models::gui::declarable::Context();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
		}

		void Entity::addClass(const int index, const QString &listindex)
		{
			const auto coreModel = new models::core::Entity(enums::core::OBJECT_TYPE);
			const auto guiModel = new models::gui::declarable::Context();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
		}

		void Entity::remove()
		{
			delete this;
		}

		void Entity::addFunction(const int index, const QString &listindex)
		{
			const auto coreModel = new models::core::Entity(enums::core::FUNCTION);
			const auto guiModel = new models::gui::declarable::Context();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
		}

		void Entity::addVariable(const int index, const QString &listindex)
		{
			const auto coreModel = new models::core::Entity(enums::core::VARIABLE);
			const auto guiModel = new models::gui::declarable::Context();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
		}

		int Entity::columnCount() const
		{
			return 1;
		}

		QVariant Entity::listColumn() const
		{
			return QVariant::fromValue(m_columslist);
        }

		QHash<int, QByteArray> Column::roleNames() const
		{
			QHash<int, QByteArray> roles;
			roles[ROLES::ENTITIES] = "entities";
			return roles;
		}

		void Column::serialize(QJsonObject& obj) const
		{
			obj["name"] = m_data.name;
			obj["description"] = m_data.description;
            obj["listIndex"] = m_data.listIndex.toString();
		}

		void Column::_deserialize(const QJsonObject& obj)
		{
			m_data.name = obj["name"].toString();
			m_data.description = obj["description"].toString();
            auto uuid = QUuid(obj["listIndex"].toString());
			if (uuid.isNull())
			{
				const auto getRandomString = [](quint32 size)
				{
					const QString possibleCharacters(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");

					QString randomString;
					for (auto i = 0; i< size; ++i)
					{
						auto index = qrand() % possibleCharacters.length();
						auto nextChar = possibleCharacters.at(index);
						randomString.append(nextChar);
					}
					return randomString;
				};
				uuid = QUuid::createUuidV5(QUuid::createUuid(), getRandomString(128));
				qDebug() << "New Uuid generated" << uuid;
			}
            m_data.listIndex = uuid;
		}

		const gui::data::EntityColumn& Column::datas() const
		{
			return m_data;
		}

		bool Column::setDatas(const gui::data::EntityColumn& data)
		{
            if (m_data == data)
                return false;
            m_data = data;
            return true;
		}

		Column::Column(QObject* parent) : QAbstractListModel(parent)
		{
		}

        int Column::rowCount(const QModelIndex& parent) const
		{
			return m_entities.count();
		}

        QVariant Column::data(const QModelIndex& index, int role) const
		{
			if (!index.isValid())
				return QVariant();
			if (role == ENTITIES)
				return QVariant::fromValue(m_entities[index.row()]);
			return QVariant();
		}

        void Column::append(Entity* e, const QModelIndex &parent)
		{
			if (!m_entities.contains(e))
			{
				beginInsertRows(parent, rowCount(), rowCount());
				m_entities.append(e);
				endInsertRows();
			}
		}

        void Column::remove(Entity* e, const QModelIndex &parent)
		{
			if (!m_entities.contains(e))
				return;
			const auto pos = m_entities.indexOf(e);
			beginRemoveRows(parent, pos, pos);
			m_entities.removeOne(e);
			endRemoveRows();
		}

		const QString& Column::name() const
		{
			return m_data.name;
		}

		const QString& Column::description() const
		{
			return m_data.description;
		}

		void Column::setName(const QString& name)
		{
			if (m_data.name == name)
				return;
			m_data.name = name;
			emit nameChanged(name);
		}

		void Column::setDescription(const QString& description)
		{
			if (m_data.description == description)
				return;
			m_data.description = description;
			emit descriptionChanged(description);
		}

		Entity* Column::parentRef() const
		{
			if (m_entities.empty())
				return nullptr;
			return m_entities.first()->parentItem();

		}
	}
}
