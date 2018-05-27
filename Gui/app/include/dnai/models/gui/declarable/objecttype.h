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
				public:
					explicit ObjectType() = default;
					const QList<ObjectType*>& classes() const;
					const QList<Variable*>& variables() const;
					const QList<Variable*>& attributes() const;
					const QList<EnumType*>& enums() const;
					const QList<ListType*>& listobjs() const;
					const QList<Function*>& functions() const;
					const QList<Function*>& methods() const;
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