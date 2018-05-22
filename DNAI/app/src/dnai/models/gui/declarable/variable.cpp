#include "dnai/models/gui/declarable/variable.h"
#include "dnai/exceptions/notimplemented.h"
#include "core.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
//				Variable::Variable(QObject* parent)
//				{
//				}
				QMap<qint32, QString> Variable::m_typeMap =
				{
					{0, "Integer"},
					{1, "Boolean"},
					{2, "String"}
				};

				QStringList Variable::m_typeList = {
					"Integer",
					"Boolean",
					"String"
				};

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
					m_data.value = obj["value"].toObject();
				}

                qint32 Variable::varType() const
				{
                    return m_data.varType;
				}

                bool Variable::setVarType(qint32 id)
				{
					if (m_data.varType == id)
						return false;
					m_data.varType = id;
					return false;
				}

				const QJsonObject &Variable::value() const
				{
					return m_data.value;
				}

				bool Variable::setValue(const QJsonObject& value)
				{
					if (m_data.value == value)
						return false;
					m_data.value = value;
					return false;
				}

				const QString& Variable::getVariableName(qint32 identifier)
				{
					return m_typeMap[identifier];
				}

				void Variable::addVariableType(qint32 identifier, const QString& name)
				{
					if (m_typeMap.find(identifier) != m_typeMap.end())
					{
						auto msg = "Type " + name + " already exist";
						throw std::runtime_error(msg.toLatin1().constData());
					}
					m_typeMap[identifier] = name;
					m_typeList.append(name);
				}

				const QMap<qint32, QString>& Variable::getVariableMap()
				{
					return m_typeMap;
				}

				const QStringList &Variable::getVariableList()
				{
					return m_typeList;
				}

				const int Variable::variableListCount()
				{
					return m_typeMap.count();
				}
			}
		}
	}
}
