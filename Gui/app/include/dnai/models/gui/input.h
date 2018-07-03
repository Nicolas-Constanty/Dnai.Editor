#ifndef DNAI_MODELS_GUI_INPUT_H
#define DNAI_MODELS_GUI_INPUT_H

#include <QObject>
#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/interfaces/ivariable.h"
#include "data/input.h"
#include "dnai/interfaces/ilinkable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Input : public QObject, public interfaces::IVariable, public interfaces::IModelData<data::Input>, public interfaces::ASerializable<Input>
			{
				Q_OBJECT
				Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
				Q_PROPERTY(QString linkedId READ linkedId WRITE setLinkedId NOTIFY idLinkedChanged)

			public:
				explicit Input(QObject * parent = nullptr);
				QString id() const;
				void setId(const QString &id);

				QString linkedId() const;
				void setLinkedId(const QString &id);

			signals:
				void idChanged(const QString &id);
				void idLinkedChanged(const QString &linkedID);
			public:
				void serialize(QJsonObject& obj) const override;
			protected:
                void _deserialize(const QJsonObject& obj) override;
			public:
				const data::Input& data() const override;
				bool setData(const data::Input& data) override;
                QUuid varType() const override;
                bool setVarType(QUuid const &id) override;
                const QString &value() const override;
                bool setValue(const QString& value) override;
				const QString name() const;
				bool setName(const QString name);

			private:
				data::Input m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_INPUT_H
