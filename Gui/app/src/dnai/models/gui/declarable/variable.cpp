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
			}
		}
	}
}
