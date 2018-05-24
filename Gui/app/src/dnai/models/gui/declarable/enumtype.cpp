#include "dnai/models/gui/declarable/enumtype.h"
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
				const QMap<QString, QJsonValue>& EnumType::values() const
				{
					return m_data.values;
				}

				const QJsonValue& EnumType::value(QString id) const
				{
					return m_data.values[id];
				}

				void EnumType::serialize(QJsonObject& obj) const
				{
					for (auto &kv : m_data.values.toStdMap())
					{
						obj[kv.first] = kv.second;
					}
				}

				void EnumType::_deserialize(const QJsonObject& obj)
				{
					for (const auto& key : obj.keys())
					{
						setValue(key, obj[key]);
					}
				}

				void EnumType::setValue(const QString &key, const QJsonValue &value)
				{
					m_data.values[key] = value;
				}

				void EnumType::setValue(const QPair<QString, QJsonValue> &value)
				{
					m_data.values[value.first] = value.second;
				}
			}
		}
	}
}
