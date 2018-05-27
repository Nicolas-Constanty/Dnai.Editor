#ifndef DNAI_MODELS_DECLARABLE_ENUMTYPE_H
#define DNAI_MODELS_DECLARABLE_ENUMTYPE_H

#include "dnai/models/gui/data/enumtype.h"
#include "entity.h"
#include <QObject>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class EnumType : public QObject, public Entity<data::EnumType, EnumType>
				{
					Q_OBJECT
				public:
					explicit EnumType() = default;
					const QMap<QString, QJsonValue> &values() const;
					const QJsonValue &value(QString id) const;

					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					virtual void _deserialize(const QJsonObject& obj) override;
					void setValue(const QString& key, const QJsonValue& value);
					void setValue(const QPair<QString, QJsonValue> &value);
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H