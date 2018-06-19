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
                    Q_UNUSED(parent)
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
					if (role == Qt::DisplayRole || role == Name)
						return QVariant::fromValue(m_values.keys().at(index.row()));
					else if (role == Type)
						return QVariant::fromValue(m_values.values().at(index.row()));
					return QVariant();
				}

				QString VarTypeList::getNameFromValue(quint32 value)
				{
					for (const auto& val : m_values.keys())
					{
						if (value == m_values[val])
							return val;
					}
					return "";
				}

				int VarTypeList::getIndexFromValue(quint32 value)
				{
					auto i = 0;
					for (const auto& val : m_values.keys())
					{
						if (value == m_values[val])
						{
							qDebug() << val;
							return i;

						}
						++i;
					}
					return 0;
				}

				int VarTypeList::getValueFromIndex(int value) const
				{
                    if (value < m_values.count())
                        return m_values.values().at(value);
                    throw std::out_of_range("No such value for index " + std::to_string(value));
				}

				const QVariant &VarTypeList::names()
				{
					m_keys = QVariant::fromValue(m_values.keys());
					return m_keys;
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
                    obj["varType"] = varType().toString();
                    obj["value"] = value();
				}

				void Variable::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
                    m_data.varType = obj["varType"].toString();
                    m_data.value = obj["value"].toString();
				}

                QUuid Variable::varType() const
				{
                    return m_data.varType;
				}

                bool Variable::setVarType(const QUuid &id)
				{
					if (m_data.varType == id)
						return false;
					m_data.varType = id;
					emit varTypeChanged(id);
                    setValue("");
                    return true;
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
                        m_varTypes = new VarTypeList();
						m_varTypes->append({ "Boolean", 1 });
						m_varTypes->append({ "Integer", 2 });
						m_varTypes->append({ "String", 5 });
					}
					return m_varTypes;
				}
			}
		}
	}
}
