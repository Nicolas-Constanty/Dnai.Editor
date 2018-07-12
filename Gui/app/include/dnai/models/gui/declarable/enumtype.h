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
                    Q_PROPERTY(QStringList values READ values NOTIFY valuesChanged)
				public:
					explicit EnumType(QObject *parent = nullptr);
                    const QStringList &values() const;
					Q_INVOKABLE void moveUp(int initial);
					Q_INVOKABLE void moveDown(int initial);
                    Q_INVOKABLE void addEntry(const QString &entry, const QString &value);
					Q_INVOKABLE void deleteEntry(const QString &entry);

					//Implementation of ISerializable
                    void serialize(QJsonObject& obj) const override;

                    QString getValue(QString const &name) const;

				signals:
					void valuesChanged(const QStringList &val);

				protected:
                    void _deserialize(const QJsonObject& obj) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H
