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
				void ListType::serialize(QJsonObject& obj) const
				{
                    Q_UNUSED(obj)
					throw exceptions::NotImplemented();
				}

				void ListType::_deserialize(const QJsonObject& obj)
				{
                    Q_UNUSED(obj)
					throw exceptions::NotImplemented();
				}
			}
		}
	}
}
