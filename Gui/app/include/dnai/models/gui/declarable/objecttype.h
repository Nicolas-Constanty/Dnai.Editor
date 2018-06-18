#ifndef DNAI_MODELS_DECLARABLE_OBJECTTYPE_H
#define DNAI_MODELS_DECLARABLE_OBJECTTYPE_H

#include "dnai/models/gui/data/objecttype.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
            {
				class ObjectType : public QObject, public Entity<data::ObjectType, ObjectType>
				{
					Q_OBJECT
                    Q_PROPERTY(QStringList attributes READ attributes NOTIFY attributesChanged)
                    Q_PROPERTY(QStringList functions READ functions NOTIFY functionsChanged)

				public:
					explicit ObjectType() = default;

                    QStringList attributes();
                    void addAttribute(QString const &name, quint32 type);
                    void removeAttribute(QString const &name);
                    void renameAttribute(QString const &name, QString const &newName);
                    Q_INVOKABLE quint32 getAttribute(QString name) const;

                public:
                    QStringList functions() const;
                    void addFunction(QString const &name);
                    void removeFunction(QString const &name);
                    void setFunctionStatus(QString const &name, bool member);
                    bool hasFunction(QString const &name);
                    Q_INVOKABLE bool isFunctionMember(QString name) const;

                signals:
                    void attributesChanged(QStringList attrs);
                    void functionsChanged(QStringList functions);

                public:
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_OBJECTTYPE_H
