#include "dnai/models/gui/output.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			Output::Output(QObject* parent) : QObject(parent)
			{
			}

			QString Output::id() const
			{
				return m_data.id.toString();
			}

			void Output::setId(const QString &id)
			{
				if (m_data.id.toString() == id)
					return;
				m_data.id = id;
				emit idChanged(id);
			}

			QString Output::linkedId() const
			{
				return m_data.linkedId.toString();
			}

			void Output::setLinkedId(const QString& id)
			{
				if (m_data.linkedId.toString() == id)
					return;
				m_data.linkedId = id;
				emit idChanged(id);
			}

			void Output::serialize(QJsonObject& obj) const
			{
				obj["id"] = m_data.id.toString();
				obj["linkedId"] = m_data.linkedId.toString();
				obj["name"] = m_data.name;
				obj["description"] = m_data.description;
				obj["index"] = m_data.index;
				obj["listIndex"] = m_data.listIndex.toString();
                obj["varType"] = m_data.varType.toString();
				obj["value"] = QJsonValue::fromVariant(m_data.value);
			}

			void Output::_deserialize(const QJsonObject& obj)
			{
				m_data.id = QUuid::fromString(obj["id"].toString());
				m_data.linkedId = QUuid::fromString(obj["linkedId"].toString());
				m_data.name = obj["name"].toString();
				m_data.description = obj["description"].toString();
				m_data.index = obj["index"].toInt();
				m_data.listIndex = QUuid::fromString(obj["listIndex"].toString());
                m_data.varType = obj["varType"].toString();
				m_data.value = obj["value"].toString();
			}

			const data::Output& Output::data() const
			{
				return m_data;
			}

			bool Output::setData(const data::Output& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}

            QUuid Output::varType() const
			{
				return m_data.varType;
			}

            bool Output::setVarType(QUuid const &id)
			{
				if (m_data.varType == id)
					return false;
				m_data.varType = id;
				return false;
			}

            const QString &Output::value() const
			{
				return m_data.value;
			}

            bool Output::setValue(const QString& value)
			{
				if (m_data.value == value)
					return false;
				m_data.value = value;
				return false;
			}

			const QString Output::name() const
			{
				return m_data.name;
			}

			bool Output::setName(const QString name)
			{
				if (m_data.name == name)
					return false;
				m_data.name = name;
				return true;
			}
		}
	}
}
