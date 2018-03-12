#include "dnai/models/gui/output.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			void Output::serialize(QJsonObject& obj) const
			{
				obj["name"] = m_data.name;
				obj["description"] = m_data.description;
				obj["index"] = m_data.index;
				obj["listIndex"] = m_data.listIndex;
				obj["varType"] = m_data.varType;
				obj["value"] = m_data.value;
			}

			void Output::_deserialize(const QJsonObject& obj)
			{
				throw exceptions::NotImplemented();
			}

			const data::Output& Output::data() const
			{
				return m_data;
			}

			bool Output::setData(const data::Output& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}

			qint32 Output::varType() const
			{
				return m_data.varType;
			}

			bool Output::setVarType(qint32 id)
			{
				if (m_data.varType == id)
					return false;
				m_data.varType = id;
				return false;
			}

			const QJsonObject &Output::value() const
			{
				return m_data.value;
			}

			bool Output::setValue(const QJsonObject& value)
			{
				if (m_data.value == value)
					return false;
				m_data.value = value;
				return false;
			}
		}
	}
}
