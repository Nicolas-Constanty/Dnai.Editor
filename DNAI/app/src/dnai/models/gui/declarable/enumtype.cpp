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
                    Q_UNUSED(obj)
					throw exceptions::NotImplemented();
				}

				void EnumType::_deserialize(const QJsonObject& obj)
				{
                    Q_UNUSED(obj)
					throw exceptions::NotImplemented();
				}
			}
		}
	}
}
