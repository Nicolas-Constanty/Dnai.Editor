#ifndef DNAI_MODELS_GUI_OUTPUT_H
#define DNAI_MODELS_GUI_OUTPUT_H

#include <QObject>
#include "dnai/interfaces/iserializable.h"
#include "data/output.h"
#include "dnai/interfaces/imodeldata.h"
#include "dnai/interfaces/ivariable.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
            class Output : public QObject, public interfaces::IVariable, public interfaces::IModelData<data::Output>, public interfaces::ASerializable<Output>
			{
				Q_OBJECT
				Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
				Q_PROPERTY(QString linkedId READ linkedId WRITE setLinkedId NOTIFY idLinkedChanged)

			public:
				explicit Output(QObject * parent = nullptr);
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
	            const data::Output& data() const override;
	            bool setData(const data::Output& data) override;
                QUuid varType() const override;
                bool setVarType(QUuid const &id) override;
                const QString &value() const override;
                bool setValue(const QString& value) override;
	            const QString name() const;
	            bool setName(QString);
            private:
				data::Output m_data;
			};
		}
	}
}

#endif //DNAI_MODELS_GUI_OUTPUT_H
