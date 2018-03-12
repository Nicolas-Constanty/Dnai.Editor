#include "dnai/models/gui/declarable/listtype.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				ListType::ListType()
				{
				}

				void ListType::serialize(QJsonObject& obj) const
				{
					throw exceptions::NotImplemented();
				}

				void ListType::_deserialize(const QJsonObject& obj)
				{
					throw exceptions::NotImplemented();
				}

				const data::ListType& ListType::data() const
				{
					return m_data;
				}

				bool ListType::setData(const data::ListType& data)
				{
					if (m_data == data)
						return false;
					m_data = data;
					return true;
				}

				int ListType::index() const
				{
					return m_data.index;
				}

				bool ListType::setIndex(int index)
				{
					if (m_data.index == index)
						return false;
					m_data.index = index;
					return true;
				}

				int ListType::listIndex() const
				{
					return m_data.listIndex;
				}

				bool ListType::setListIndex(int listIndex)
				{
					if (m_data.listIndex == listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& ListType::description() const
				{
					return m_data.description;
				}

				bool ListType::setDescription(const QString& description)
				{
					if (m_data.description == description)
						return false;
					m_data.description = description;
					return true;
				}
			}
		}
	}
}
