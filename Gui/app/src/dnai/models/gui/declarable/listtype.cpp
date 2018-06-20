#include "dnai/models/gui/declarable/listtype.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				void ListType::serialize(QJsonObject& obj) const
				{
                    Entity::serialize(obj);

                    obj["stored_type"] = m_data.stored_type.toString();
				}

				void ListType::_deserialize(const QJsonObject& obj)
				{
                    Entity::_deserialize(obj);

                    m_data.stored_type = obj["stored_type"].toString();
                }

                QUuid ListType::storedType() const
                {
                    return m_data.stored_type;
                }

                void ListType::setStoredType(const QUuid &value)
                {
                    if (value == m_data.stored_type)
                        return;
                    m_data.stored_type = value;
                    emit storedTypeChanged(storedType());
                }
			}
		}
	}
}
