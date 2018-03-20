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
					throw exceptions::NotImplemented();
				}

				void ListType::_deserialize(const QJsonObject& obj)
				{
					throw exceptions::NotImplemented();
				}
			}
		}
	}
}
