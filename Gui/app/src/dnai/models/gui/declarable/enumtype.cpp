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
					return m_data.values;
				}

				void EnumType::moveUp(int initial)
				{
					if (initial < 0)
						return;
					const auto start = initial % m_data.values.length();
					const auto end = (start <= 0) ? m_data.values.length() - 1 : start - 1;
					m_data.values.swap(start, end);
					emit valuesChanged(m_data.values);
				}

				void EnumType::addEntry(const QString& entry)
				{
					if (entry.isEmpty())
					{
						m_data.values.append(QString("Empty ") + QString::number(m_data.values.length()));
						emit valuesChanged(m_data.values);
						return;
					}
					for (const auto &val : m_data.values)
						if (val == entry)
							return;
					m_data.values.append(entry);
					emit valuesChanged(m_data.values);
				}

				void EnumType::deleteEntry(const QString& entry)
				{
					m_data.values.removeOne(entry);
					emit valuesChanged(m_data.values);
				}

				void EnumType::moveDown(int initial)
				{
					if (initial < 0)
						return;
					const auto start = initial % m_data.values.length();
					const auto end = (start + 1) % m_data.values.length();
					m_data.values.swap(start, end);
					emit valuesChanged(m_data.values);
				}

				void EnumType::serialize(QJsonObject& obj) const
				{
					QJsonArray arr;
					for (auto &val : m_data.values)
					{
						arr.append(val);
					}
					obj["enumvalues"] = arr;
				}

				void EnumType::setValues(const QStringList& list)
				{
					if (list == m_data.values)
						return;
					m_data.values = list;
					emit valuesChanged(list);
				}

				void EnumType::_deserialize(const QJsonObject& obj)
				{
					for (const auto& val : obj["enumvalues"].toArray())
					{
						addEntry(val.toString());
					}
				}
			}
		}
	}
}
