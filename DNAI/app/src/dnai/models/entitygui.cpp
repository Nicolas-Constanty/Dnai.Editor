#include "dnai/models/entitygui.h"

namespace dnai
{
	namespace models
	{
		bool EntityGuiData::operator!=(const EntityGuiData& other) const
		{
			return !(*this == other);
		}

		bool EntityGuiData::operator==(const EntityGuiData& other) const
		{
			return (index == other.index && listIndex == other.listIndex && description == other.description);
		}

		const EntityGuiData& EntityGUI::data() const
		{
			return m_data;
		}

		bool EntityGUI::setData(const EntityGuiData& data)
		{
			if (m_data == data)
				return false;
			m_data = data;
			return true;
		}

		int EntityGUI::index() const
		{
			return m_data.index;
		}

		bool EntityGUI::setIndex(const int index)
		{
			if (m_data.index == index)
				return false;
			m_data.index = index;
			return true;
		}

		int EntityGUI::listIndex() const
		{
			return m_data.listIndex;
		}

		bool EntityGUI::setListIndex(const int listIndex)
		{
			if (m_data.listIndex == listIndex)
				return false;
			m_data.listIndex = listIndex;
			return true;
		}

		const QString& EntityGUI::description() const
		{
			return m_data.description;
		}

		bool EntityGUI::setDescription(const QString& description)
		{
			if (m_data.description == description)
				return false;
			m_data.description = description;
			return true;
		}
	}
}