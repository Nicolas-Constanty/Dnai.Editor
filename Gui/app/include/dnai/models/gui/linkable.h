#ifndef DNAI_MODELS_GUI_LINK_H
#define DNAI_MODELS_GUI_LINK_H

#include <QObject>
#include "dnai/models/gui/data/linkable.h"
#include "dnai/interfaces/iserializable.h"
#include "dnai/interfaces/imodeldata.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			class Linkable : public QObject, public interfaces::IModelData<data::Linkable>, public interfaces::ASerializable<data::Linkable>
			{
				Q_OBJECT
				Q_PROPERTY(QString id READ id WRITE setId NOTIFY instructionChanged)
				Q_PROPERTY(QString linkedId READ linkedId WRITE se NOTIFY outputChanged)

			public:
				const QString id() const;
				void setId(const QString &id);

				const QString linkedId() const;
				void setLinkedID(const QString &id);

			signals:
				void idChanged(const QString &id);
				void idLinkedChanged(const QString &linkedID);

				void serialize(QJsonObject& obj) const override;
			protected:
				void _deserialize(const QJsonObject& obj) override;
			public:
				const data::Linkable& data() const override;
				bool setData(const data::Linkable& data) override;

			private:
				data::Linkable m_data;
			};
		}
	}
}


#endif //DNAI_MODELS_GUI_LINK_H