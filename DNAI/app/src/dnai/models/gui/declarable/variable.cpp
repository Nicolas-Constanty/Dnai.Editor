#include "dnai/models/gui/declarable/variable.h"
#include "dnai/exceptions/notimplemented.h"

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

				void Variable::serialize(QJsonObject& obj) const
				{
					Entity::serialize(obj);
					obj["varType"] = m_data.varType;
					obj["value"] = m_data.value;
				}

				void Variable::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);
					m_data.varType = obj["varType"].toInt();
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
			}
		}
	}
}
