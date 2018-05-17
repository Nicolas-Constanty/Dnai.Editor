#include <QMetaProperty>
#include <QDebug>
#include "dnai/models/property.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace models
	{
		Property::Property(QObject* obj, const QList<QString>& editableprops)
		{
			m_obj = obj;
			for (auto j = 0; j < editableprops.count(); j++)
			{
				for (auto i = 0; i < obj->metaObject()->propertyCount(); i++)
				{
					if (obj->metaObject()->property(i).name() == editableprops.at(j))
					{
						m_editableIndex.append(editableprops.at(j));
						break;
					}
				}
            }
		}

		int Property::rowCount(const QModelIndex& parent) const
		{
			return m_editableIndex.count();
		}

		int Property::columnCount(const QModelIndex& parent) const
		{
			return 2;
		}

		QVariant Property::data(const QModelIndex& index, int role) const
		{
			if (!index.isValid())
                return QVariant();
			if (role == ROLES::VALUE)
			{
				return m_obj->property(m_editableIndex.at(index.row()).toLatin1().constData());
			}
			if (role == ROLES::NAME)
			{
				return QVariant::fromValue(m_editableIndex.at(index.row()));
			}
			if (role == ROLES::ITEM)
			{
				return QVariant::fromValue(m_obj);
			}
			return QVariant();
		}

		void Property::setProp(int row, const QVariant& value)
		{
			auto obj = dynamic_cast<Entity*>(m_obj);
			if (obj)
			{
				const auto n = getPropName(row);
				if (n == "name")
					obj->setName(value.toString());
				else if (n == "description")
					obj->setDescription(value.toString());
				else if (n == "visibility")
					obj->setVisibility(value.toInt());
				else if (n == "type")
					obj->setEntityType(value.toInt() + 1);
			}
		}


		QString Property::getPropName(int row) const
		{
			return m_editableIndex.at(row);
		}

		Entity* Property::model() const
		{
			return dynamic_cast<Entity *>(m_obj);
		}

		QHash<int, QByteArray> Property::roleNames() const
		{
			QHash<int, QByteArray> roles;
			roles[ROLES::NAME] = "name";
			roles[ROLES::VALUE] = "value";
			roles[ROLES::ITEM] = "item";
			return roles;
		}
	}
}
