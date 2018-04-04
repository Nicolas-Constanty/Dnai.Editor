#include <QJsonArray>
#include "dnai/models/entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/context.h"

#include "dnai/core/handlermanager.h"

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

		QString Entity::listIndex() const
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

		Entity* Entity::parentRef() const
		{
			return parentItem();
		}

		const QMap<QUuid, Column*>& Entity::columns()
		{
			return m_columns;
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
            if (coreModel()->setEntityType(static_cast<enums::core::ENTITY>(type)))
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
				c->setListIndex(uuid.toString());
				m_columslist.append(c);
				m_columns[uuid] = c;
			}
			m_columns[uuid]->append(child);
			emit entityChildrenChanged(child);
		}

		void Entity::serialize(QJsonObject& obj) const
		{
			QJsonArray ca;
			for (auto c : m_columns)
			{
				QJsonObject tmp;
				c->serialize(tmp);
				ca.append(tmp);
			}
			obj["columns"] = ca;
			if (m_dataCore == nullptr) return;
			m_dataCore->serialize(obj);
			m_dataGUI->serialize(obj);
			QJsonArray ea;
            for (auto child : childrenItem())
			{
				QJsonObject o;
				child->serialize(o);
				ea.append(o);
			}
			obj["entities"] = ea;
		}

		void Entity::_deserialize(const QJsonObject& obj)
		{
            foreach(const auto column, obj["columns"].toArray()) {
                const auto col = Column::deserialize(column.toObject());
                m_columns[col->datas().listIndex] = col;
				m_columslist.append(col);
			}
			m_dataCore->setName(obj["name"].toString());
            m_dataCore->setVisibility(static_cast<enums::core::VISIBILITY>(obj["visibility"].toInt()));
            switch (m_dataCore->entityType())
            {
            case enums::core::ENTITY::UNDEFINED: break;
            case enums::core::ENTITY::CONTEXT:
            {
                m_dataGUI = gui::declarable::Context::deserialize(obj);
                break;
            }
            case enums::core::ENTITY::VARIABLE:
            {
                m_dataGUI = gui::declarable::Variable::deserialize(obj);
                break;
            }
            case enums::core::ENTITY::FUNCTION:
            {
                m_dataGUI = gui::declarable::Function::deserialize(obj);
                break;
            }
            case enums::core::ENTITY::DATA_TYPE: break;
            case enums::core::ENTITY::ENUM_TYPE:
            {
                m_dataGUI = gui::declarable::EnumType::deserialize(obj);
                break;
            }
            case enums::core::ENTITY::OBJECT_TYPE:
            {
                m_dataGUI = gui::declarable::ObjectType::deserialize(obj);
                break;
            }
            case enums::core::ENTITY::LIST_TYPE:
            {
                m_dataGUI = gui::declarable::ListType::deserialize(obj);
                break;
            }
            default: ;
            }
			
            foreach(const auto classe, obj["entities"].toArray()) {
				QJsonObject o = classe.toObject();
				qDebug() << o["name"].toString() << o["type"].toInt();
                const auto coreModel = new models::core::Entity(static_cast<enums::core::ENTITY>(o["type"].toInt()));
                Entity *parent = this;
                const auto entity = Entity::deserialize(o, coreModel, parent);
                qDebug() << entity->listIndex();
				if (QUuid(entity->listIndex()).isNull() && !m_columns.empty())
					entity->setListIndex(m_columns.keys().first().toString());
				appendChild(entity);
			}

   //         foreach(const auto context, obj["contexts"].toArray()) {
   //             const auto coreModel = new models::core::Entity(enums::core::CONTEXT);
   //             Entity *parent = this;
   //             const auto entity = deserialize(context.toObject(), coreModel, parent);
			//	appendChild(entity);
			//}

   //         foreach(const auto variable, obj["variables"].toArray()) {
   //             const auto coreModel = new models::core::Entity(enums::core::VARIABLE);
   //             Entity *parent = this;
   //             const auto entity = Entity::deserialize(variable.toObject(),coreModel, parent);
			//	appendChild(entity);
			//}

   //         foreach(const auto function, obj["functions"].toArray()) {
   //             const auto coreModel = new models::core::Entity(enums::core::FUNCTION);
   //             Entity *parent = this;
   //             const auto entity = Entity::deserialize(function.toObject(), coreModel, parent);
			//	appendChild(entity);
			//}
		}

		void Entity::addContext(const int index, const QString &listindex)
		{
            const auto coreModel = new models::core::Entity(enums::core::ENTITY::CONTEXT);
            const auto guiModel = new models::gui::declarable::Context();
			guiModel->setIndex(index);
            qDebug() << listindex;
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
			entity->declare();
		}

		void Entity::addClass(const int index, const QString &listindex)
		{
            const auto coreModel = new models::core::Entity(enums::core::ENTITY::OBJECT_TYPE);
            const auto guiModel = new models::gui::declarable::ObjectType();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
			entity->declare();
		}

        void Entity::declare()
        {
            dnai::core::HandlerManager::Instance().Declarator().declare(*this);
        }

		void Entity::remove()
		{
			auto p = parentItem();
			for (auto c : p->columns())
			{
				c->remove(this);
            }
            dnai::core::HandlerManager::Instance().Declarator().remove(*this);
			parentItem()->removeOne(this);
            delete this;
		}

		void Entity::addFunction(const int index, const QString &listindex)
		{
            const auto coreModel = new models::core::Entity(enums::core::ENTITY::FUNCTION);
            const auto guiModel = new models::gui::declarable::Function();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
			entity->declare();
		}

		void Entity::addVariable(const int index, const QString &listindex)
		{
            const auto coreModel = new models::core::Entity(enums::core::ENTITY::VARIABLE);
            const auto guiModel = new models::gui::declarable::Variable();
			guiModel->setIndex(index);
			guiModel->setListIndex(listindex);
			Entity *parent = this;
			const auto entity = new Entity(coreModel, parent, guiModel);
			appendChild(entity);
			entity->declare();
		}

		int Entity::columnCount() const
		{
			return 1;
		}

		QVariant Entity::listColumn() const
		{
			return QVariant::fromValue(m_columslist);
        }

		int Entity::row() const
		{
			return IModel<Entity>::row();
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
                const auto getRandomString = [](int size)
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
            Q_UNUSED(parent)
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

		QString Column::listIndex() const
		{
			return m_data.listIndex.toString();
		}

		void Column::setListIndex(const QString& s)
		{
			if (m_data.listIndex.toString() == s)
				return;
			m_data.listIndex = QUuid::fromString(s);
			emit listIndexChanged(s);
		}

		Entity* Column::parentRef() const
		{
			if (m_entities.empty())
				return nullptr;
			return m_entities.first()->parentItem();

		}
	}
}
