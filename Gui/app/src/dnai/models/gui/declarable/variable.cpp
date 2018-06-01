#include "dnai/models/gui/declarable/variable.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/models/gui/entitylist.h"
#include "core.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				EntityList *Variable::m_variables = new EntityList(new QList<models::Entity*>());
				VarTypeList *Variable::m_varTypes = nullptr;

				int VarTypeList::rowCount(const QModelIndex& parent) const
				{
					return m_values.count();
				}

				void VarTypeList::append(const QString &name, const quint32 value)
				{
					if (m_values.find(name) != m_values.end()) return;
					beginInsertRows(QModelIndex(), m_values.count(), m_values.count());
					m_values.insert(name, value);
					endInsertRows();
				}

				void VarTypeList::append(const QPair<QString, quint32> &value)
				{
					if (m_values.find(value.first) != m_values.end()) return;
					beginInsertRows(QModelIndex(), m_values.count(), m_values.count());
					m_values.insert(value.first, value.second);
					endInsertRows();
				}

				void VarTypeList::remove(const QString& name)
				{
					auto index = 0;
					for (const auto& i : m_values.keys())
					{
						if (i == name)
							break;
						index++;
					}
					beginRemoveRows(QModelIndex(), index, index);
					m_values.remove(name);
					endRemoveRows();
				}

				QVariant VarTypeList::data(const QModelIndex& index, int role) const
				{
					if (!index.isValid())
						return QVariant();
					if (role == Name)
						return QVariant::fromValue(m_values.keys().at(index.row()));
					else if (role == Type)
						return QVariant::fromValue(m_values.values().at(index.row()));
					return QVariant();
				}

				QHash<int, QByteArray> VarTypeList::roleNames() const
				{
					QHash<int, QByteArray> roles;
					roles[Name] = "name";
					roles[Type] = "varType";
					return roles;
				}

				Variable::Variable(QObject* parent) : QObject(parent)
				{
				}

				void Variable::serialize(QJsonObject& obj) const
				{
					Entity::serialize(obj);
                    obj["varType"] = varType();
                    obj["value"] = value();
				}

				void Variable::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
                    m_data.varType = static_cast<::core::EntityID>(obj["varType"].toInt());
                    m_data.value = obj["value"].toString();
				}

                qint32 Variable::varType() const
				{
                    return m_data.varType;
				}

                bool Variable::setVarType(const qint32 id)
				{
					if (m_data.varType == id)
						return false;
					m_data.varType = id;
					emit varTypeChanged(id);
					return false;
				}

				const QString &Variable::value() const
				{
					return m_data.value;
				}

				bool Variable::setValue(const QString& value)
				{
					if (m_data.value == value)
						return false;
					m_data.value = value;
					emit valueChanged(value);
					return false;
				}

				EntityList* Variable::variables()
				{
					return m_variables;
				}

				VarTypeList* Variable::varTypes()
				{
					if (!m_varTypes)
					{
						m_varTypes->append({ "Integer", 2 });
						m_varTypes->append({ "Boolean", 1 });
						m_varTypes->append({ "String", 5 });
					}
					return m_varTypes;
				}
			}
		}
	}
}
