#include "dnai/models/gui/flowlink.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			const data::FlowLink& FlowLink::data() const
			{
				return m_data;
			}

			bool FlowLink::setData(const data::FlowLink& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}

			void FlowLink::serialize(QJsonObject& obj) const
			{
				obj["from"] = m_data.from.toString();
				obj["to"] = m_data.to.toString();
				obj["out_index"] = static_cast<int>(m_data.outIndex);
			}

			void FlowLink::_deserialize(const QJsonObject& obj)
			{
				m_data.from = obj["from"].toString();
				m_data.to = obj["to"].toString();
				m_data.outIndex = obj["out_index"].toInt();
			}
		}
	}
}