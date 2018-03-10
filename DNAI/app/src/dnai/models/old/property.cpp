#include "dnai/models/property.h"

namespace dnai
{
	namespace models
	{
		Property::Property(QObject* parent) : QObject(parent), m_model(nullptr)
		{
		}

		Property::Property(QObject* model, QObject* parent) : QObject(parent), m_model(model)
		{
		}

        Property::Property(const QString& name, const QVariant& value, QObject* model, QObject* parent): QObject(parent),
            m_name(name),
            m_value(value),
            m_model(model)
		{
		}

		Property::~Property() = default;

		const QString& Property::name() const
		{
			return m_name;
		}

		void Property::setName(const QString& name)
		{
			if (name == m_name)
				return;
			m_name = name;
			emit nameChanged(name);
		}

		const QVariant& Property::value() const
		{
			return m_value;
		}

		void Property::setValue(const QVariant& value)
		{
			if (value == m_value)
				return;
			m_value = value;
			if (m_model)
				m_model->setProperty(m_name.toLatin1().data(), value);
			emit valueChanged(value);
		}
	}
}
