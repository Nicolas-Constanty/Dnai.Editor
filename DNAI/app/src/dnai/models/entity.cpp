#include "dnai/models/entity.h"
#include <QDebug>

namespace dnai
{
	namespace models
	{
		Entity::Entity(QObject* parent) : QAbstractListModel(parent)
		{
		}

		Entity::Entity(IModel* model, QObject* parent) : QAbstractListModel(parent)
		{
            qDebug() << "[ENTITY CREATE]" << model->editableProperties();
			const auto obj = dynamic_cast<QObject *>(model);
			for(const auto& prop : model->editableProperties())
			{
				addModel(new Property(prop, obj->property(prop.toLatin1().data()), obj));
			}
		}

		int Entity::rowCount(const QModelIndex& parent) const
		{
            Q_UNUSED(parent)
			return m_properties.count();
		}

		QVariant Entity::data(const QModelIndex& index, int role) const
		{
			if (index.row() < 0 || index.row() >= m_properties.count())
				return QVariant();

			const auto item = m_properties[index.row()];
			if (role == Roles::ITEM_ROLE)
				return QVariant::fromValue(item);
			if (role == Roles::NAME)
				return QVariant::fromValue(item->name());
			if (role == Roles::VALUE)
				return item->value();
			return QVariant();
		}

		bool Entity::removeRow(int row, const QModelIndex& parent)
		{
			Q_UNUSED(parent);
			beginRemoveRows(QModelIndex(), row, row);
			m_properties.removeAt(row);
			endRemoveRows();
			return true;
		}

		void Entity::addModel(Property* c)
		{
			beginInsertRows(QModelIndex(), rowCount(), rowCount());
			m_properties << c;
			endInsertRows();

		}

		QHash<int, QByteArray> Entity::roleNames() const
		{
			QHash<int, QByteArray> roles;
			roles[Roles::VALUE] = "item";
			roles[Roles::NAME] = "name";
			roles[Roles::ITEM_ROLE] = "item";
			return roles;
		}
	}
}
