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
				EnumType::EnumType(QObject* parent) : QObject(parent)
				{

				}

                const QStringList& EnumType::values() const
				{
                    return m_data.names;
				}

				void EnumType::moveUp(int initial)
				{
					if (initial < 0)
						return;
                    const auto start = initial % m_data.names.length();
                    const auto end = (start <= 0) ? m_data.names.length() - 1 : start - 1;
                    m_data.names.swap(start, end);
                    emit valuesChanged(values());
				}

                void EnumType::addEntry(const QString& entry, const QString &value)
                {
                    if (m_data.values.contains(entry))
                        return;
                    m_data.names.append(entry);
                    m_data.values[entry] = value;
                    emit valuesChanged(values());
				}

				void EnumType::deleteEntry(const QString& entry)
				{
                    m_data.names.removeOne(entry);
                    m_data.values.remove(entry);
                    emit valuesChanged(values());
				}

				void EnumType::moveDown(int initial)
				{
					if (initial < 0)
						return;
                    const auto start = initial % m_data.names.length();
                    const auto end = (start + 1) % m_data.names.length();
                    m_data.names.swap(start, end);
                    emit valuesChanged(values());
				}

				void EnumType::serialize(QJsonObject& obj) const
				{
					QJsonArray arr;

                    for (QString const &val : m_data.names)
					{
                        QJsonObject obj;

                        obj["key"] =  val;
                        obj["value"] = m_data.values[val];
                        arr.append(obj);
					}
                    obj["enumvalues"] = arr;
                }

                QString EnumType::getValue(const QString &name) const
                {
                    return m_data.values.value(name);
                }

				void EnumType::_deserialize(const QJsonObject& obj)
				{
                    for (const QJsonValue& val : obj["enumvalues"].toArray())
					{
                        addEntry(val.toObject().value("key").toString(), val.toObject().value("value").toString());
					}
				}
			}
		}
	}
}
