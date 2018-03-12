#include "dnai/models/gui/declarable/entity.h"
#include "dnai/exceptions/notimplemented.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            namespace declarable {
                bool Entity::setData(const data::Entity& data)
                {
                    if (m_data == data)
                        return false;
                    m_data = data;
                    return true;
                }

                int Entity::index() const
                {
                    return m_data.index;
                }

                bool Entity::setIndex(const int index)
                {
                    if (m_data.index == index)
                        return false;
                    m_data.index = index;
                    return true;
                }

                int Entity::listIndex() const
                {
                    return m_data.listIndex;
                }

                bool Entity::setListIndex(const int listIndex)
                {
                    if (m_data.listIndex == listIndex)
                        return false;
                    m_data.listIndex = listIndex;
                    return true;
                }

                const QString& Entity::description() const
                {
                    return m_data.description;
                }

                bool Entity::setDescription(const QString& description)
                {
                    if (m_data.description == description)
                        return false;
                    m_data.description = description;
                    return true;
                }

	            Entity::Entity()
	            {
	            }

                const data::Entity& Entity::data() const
                {
                    return m_data;
                }

                Entity::~Entity()
                {
                }

	            void Entity::serialize(QJsonObject& obj) const
	            {
					throw exceptions::NotImplemented();
	            }

	            void Entity::_deserialize(const QJsonObject& obj)
	            {
					throw exceptions::NotImplemented();
	            }
            }
		}
	}
}
