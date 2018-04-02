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
                    Q_UNUSED(obj)
                    exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
				}

				void ListType::_deserialize(const QJsonObject& obj)
				{
                    Q_UNUSED(obj)
                    exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
				}
			}
		}
	}
}
