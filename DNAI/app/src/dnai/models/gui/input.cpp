#include "dnai/models/gui/input.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			void Input::serialize(QJsonObject& obj) const
			{
				obj["name"] = m_data.name;
				obj["description"] = m_data.description;
				obj["index"] = m_data.index;
                obj["listIndex"] = m_data.listIndex.toString();
				obj["varType"] = m_data.varType;
				obj["value"] = m_data.value;
			}

			void Input::_deserialize(const QJsonObject& obj)
			{
                Q_UNUSED(obj)
                exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
			}

			const data::Input& Input::data() const
			{
				return m_data;
			}

			bool Input::setData(const data::Input& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}

			qint32 Input::varType() const
			{
				return m_data.varType;
			}

			bool Input::setVarType(qint32 id)
			{
				if (m_data.varType == id)
					return false;
				m_data.varType = id;
				return false;
			}

			const QJsonObject &Input::value() const
			{
				return m_data.value;
			}

			bool Input::setValue(const QJsonObject& value)
			{
				if (m_data.value == value)
					return false;
				m_data.value = value;
				return false;
			}
		}
	}
}
