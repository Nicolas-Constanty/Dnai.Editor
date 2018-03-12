#include "dnai/models/gui/declarable/enumtype.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				EnumType::EnumType()
				{
				}

				void EnumType::serialize(QJsonObject& obj) const
				{
					throw exceptions::NotImplemented();
				}

				void EnumType::_deserialize(const QJsonObject& obj)
				{
					throw exceptions::NotImplemented();
				}

				const data::EnumType& EnumType::data() const
				{
					return m_data;
				}

				bool EnumType::setData(const data::EnumType& data)
				{
					if (m_data == data)
						return false;
					m_data = data;
					return true;
				}

				int EnumType::index() const
				{
					return m_data.index;
				}

				bool EnumType::setIndex(int index)
				{
					if (m_data.index == index)
						return false;
					m_data.index = index;
					return true;
				}

				int EnumType::listIndex() const
				{
					return m_data.listIndex;
				}

				bool EnumType::setListIndex(int listIndex)
				{
					if (m_data.listIndex == listIndex)
						return false;
					m_data.listIndex = listIndex;
					return true;
				}

				const QString& EnumType::description() const
				{
					return m_data.description;
				}

				bool EnumType::setDescription(const QString& description)
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
