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
				Variable::Variable(QObject* parent)
				{
				}

				void Variable::serialize(QJsonObject& obj) const
				{
					obj["description"] = m_data.description;
					obj["index"] = m_data.index;
					obj["listIndex"] = m_data.listIndex;
					obj["varType"] = m_data.varType;
					obj["value"] = m_data.value;
				}

				void Variable::_deserialize(const QJsonObject& obj)
				{
					m_data.description = obj["description"].toString();
					m_data.index = obj["index"].toInt();
					m_data.listIndex = obj["listIndex"].toInt();
					m_data.varType = obj["varType"].toInt();
					m_data.value = obj["value"].toObject();
				}

				const data::Variable& Variable::data() const
				{
					return m_data;
				}

				bool Variable::setData(const data::Variable& data)
				{
					if (m_data == data)
						return false;
					m_data = data;
					return true;
				}

				int Variable::index() const
				{
					return m_data.index;
				}

				bool Variable::setIndex(int index)
				{
					if (index == m_data.index)
						return false;
					m_data.index = index;
					return true;
				}

				int Variable::listIndex() const
				{
					return m_data.listIndex;
				}

				bool Variable::setListIndex(int listIndex)
				{
					if (listIndex == m_data.listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& Variable::description() const
				{
					return m_data.description;
				}

				bool Variable::setDescription(const QString& description)
				{
					if (description == m_data.description)
						return false;
					m_data.description = description;
					return true;
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
