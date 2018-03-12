#include "dnai/models/gui/flow.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			void Flow::serialize(QJsonObject& obj) const
			{
				throw exceptions::NotImplemented();
			}

			void Flow::_deserialize(const QJsonObject& obj)
			{
				throw exceptions::NotImplemented();
			}

			const data::Flow& Flow::data() const
			{
				return m_data;
			}

			bool Flow::setData(const data::Flow& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}
		}
	}
}
