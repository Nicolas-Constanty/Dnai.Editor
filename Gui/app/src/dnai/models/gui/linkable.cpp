#include "dnai/models/gui/linkable.h"
#include <QString>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			QString Linkable::id() const
			{
				return m_data.id.toString();
			}

			void Linkable::setId(const QString &id)
			{
				if (m_data.id.toString() == id)
					return;
				m_data.id = id;
				emit idChanged(id);
			}

			QString Linkable::linkedId() const
			{
				return m_data.linkedId.toString();
			}

			void Linkable::setLinkedId(const QString& id)
			{
				if (m_data.linkedId.toString() == id)
					return;
				m_data.linkedId = id;
				emit idChanged(id);
			}

			void Linkable::serialize(QJsonObject& obj) const
			{
				obj["id"] = m_data.id.toString();
				obj["linkedId"] = m_data.linkedId.toString();
			}

			void Linkable::_deserialize(const QJsonObject& obj)
			{
				m_data.id = QUuid::fromString(obj["id"].toString());
				m_data.linkedId = QUuid::fromString(obj["linkedId"].toString());
			}

			const data::Linkable& Linkable::data() const
			{
				return m_data;
			}

			bool Linkable::setData(const data::Linkable& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}
		}
	}
}
