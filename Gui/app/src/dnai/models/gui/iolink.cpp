#include "dnai/models/gui/iolink.h"
#include <QDebug>
namespace dnai
{
	namespace models
	{
		namespace gui
		{
			const data::IoLink& IoLink::data() const
			{
				return m_data;
			}

			bool IoLink::setData(const data::IoLink& data)
			{
				if (data == m_data)
					return false;
				m_data = data;
				return true;
			}

			void IoLink::serialize(QJsonObject& obj) const
            {
				obj["inputName"] = m_data.inputName;
				obj["outputName"] = m_data.outputName;
				obj["inputUuid"] = m_data.inputUuid.toString();
				obj["outputUuid"] = m_data.outputUuid.toString();
			}

			void IoLink::_deserialize(const QJsonObject& obj)
			{
				m_data.inputName = obj["inputName"].toString();
				m_data.outputName = obj["outputName"].toString();
				m_data.inputUuid = obj["inputUuid"].toString();
				m_data.outputUuid = obj["outputUuid"].toString();
			}
		}
	}
}
