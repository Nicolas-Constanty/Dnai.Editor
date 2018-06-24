#include "dnai/models/gui/input.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			Input::Input(QObject* parent) : QObject(parent)
			{
			}

			QString Input::id() const
			{
				return m_data.id.toString();
			}

			void Input::setId(const QString &id)
			{
				if (m_data.id.toString() == id)
					return;
				m_data.id = id;
				emit idChanged(id);
			}

			QString Input::linkedId() const
			{
				return m_data.linkedId.toString();
			}

			void Input::setLinkedId(const QString& id)
			{
				if (m_data.linkedId.toString() == id)
					return;
				m_data.linkedId = id;
				emit idChanged(id);
			}

			void Input::serialize(QJsonObject& obj) const
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

			void Input::_deserialize(const QJsonObject& obj)
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

			const data::Input& Input::data() const
			{
				return m_data;
			}

			bool Input::setData(const data::Input& data)
			{
				if (m_data == data)
					return false;
				m_data = data;
				return true;
			}

            QUuid Input::varType() const
			{
				return m_data.varType;
			}

            bool Input::setVarType(QUuid const &id)
			{
				if (m_data.varType == id)
					return false;
				m_data.varType = id;
				return false;
			}

            const QString &Input::value() const
			{
				return m_data.value;
			}

            bool Input::setValue(const QString& value)
			{
				if (m_data.value == value)
					return false;
				m_data.value = value;
				return false;
			}

			const QString Input::name() const
			{
				return m_data.name;
			}

			bool Input::setName(const QString name)
			{
				if (m_data.name == name)
					return false;
				m_data.name = name;
				return true;
			}
		}
	}
}
