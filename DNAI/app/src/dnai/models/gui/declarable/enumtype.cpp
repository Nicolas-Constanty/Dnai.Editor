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
				void EnumType::serialize(QJsonObject& obj) const
				{
					throw exceptions::NotImplemented();
				}

				void EnumType::_deserialize(const QJsonObject& obj)
				{
					throw exceptions::NotImplemented();
				}
			}
		}
	}
}
