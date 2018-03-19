#include "dnai/models/entitytree.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
    {
    EntityTree::EntityTree(QObject *parent) : QAbstractItemModel(parent), m_rootItem(nullptr)
    {

    }

    QModelIndex EntityTree::index(const int row, const int column, const QModelIndex& parent) const
        {
			if (!hasIndex(row, column, parent))
            {
				return {};
            }
			Entity *parentItem;

			if (!parent.isValid())
				parentItem = m_rootItem;
			else
                parentItem = static_cast<Entity*>(parent.internalPointer());
			const auto childItem = parentItem->child(row);
			if (childItem)
            {
				return createIndex(row, column, childItem);
            }
			return {};
		}

		QModelIndex EntityTree::parent(const QModelIndex& child) const
		{
			if (!child.isValid())
				return {};

			const auto childItem = static_cast<Entity*>(child.internalPointer());
			const auto parentItem = childItem->parentItem();

			if (parentItem == m_rootItem)
				return {};

			return createIndex(parentItem->row(), 0, parentItem);
		}

		int EntityTree::rowCount(const QModelIndex& parent) const
		{
			Entity *parentItem;
			if (parent.column() > 0)
				return 0;

			if (!parent.isValid())
				parentItem = m_rootItem;
			else
				parentItem = static_cast<Entity*>(parent.internalPointer());
			return parentItem->childCount();
		}

		int EntityTree::columnCount(const QModelIndex& parent) const
		{
			if (parent.isValid())
                return static_cast<Entity*>(parent.internalPointer())->columnCount();
			return m_rootItem->columnCount();
		}

		QVariant EntityTree::data(const QModelIndex& index, const int role) const
        {
			if (!index.isValid())
                return QVariant();
			const auto entity = static_cast<Entity*>(index.internalPointer());
			switch (role)
			{
			case ID:
				return entity->id();
			case TYPE:
				return entity->entityType();
			case CONTAINER_ID:
				return entity->containerId();
			case NAME:
			case Qt::DisplayRole:
				return QVariant::fromValue(entity->name());
			case VISIBILITY:
				return entity->visibility();
			case INDEX:
				return entity->index();
			case LISTINDEX:
				return entity->listIndex();
			case DESCRIPTION:
                return entity->description();
            case MODEL:
				return QVariant::fromValue(entity);
			default: 
				return QVariant();
			}
		}

		int EntityTree::getRoleKey(QString rolename) const
		{
			return roleNames().key(rolename.toLatin1());
		}

		QHash<int, QByteArray> EntityTree::roleNames() const
		{
			QHash<int, QByteArray> roles;
			roles[ROLES::ID] = "id";
			roles[ROLES::TYPE] = "type";
			roles[ROLES::CONTAINER_ID] = "containerId";
			roles[ROLES::NAME] = "name";
			roles[ROLES::VISIBILITY] = "visibility";
			roles[ROLES::INDEX] = "index";
			roles[ROLES::LISTINDEX] = "listIndex";
			roles[ROLES::DESCRIPTION] = "description";
			roles[ROLES::CORE_MODEL] = "coreModel";
			roles[ROLES::GUI_MODEL] = "guiModel";
			roles[ROLES::MODEL] = "modelobj";
			return roles;
		}
	}
}
