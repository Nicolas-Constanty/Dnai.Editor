#ifndef DNAI_MODELS_DECLARABLE_CONTEXT_H
#define DNAI_MODELS_DECLARABLE_CONTEXT_H

#include "dnai/models/gui/data/context.h"
#include "entity.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class Context : public QObject, public Entity<data::Context, Context>
				{
					Q_OBJECT
				public:
					explicit Context(QObject *parent = nullptr);
					const QList<Context*>& contexts() const;
					const QList<ObjectType*>& classes() const;
					const QList<Variable*>& variables() const;
					const QList<EnumType*>& enums() const;
					const QList<ListType*>& listobjs() const;
					const QList<Function*>& functions() const;
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
                    void _deserialize(const QJsonObject& obj) override;
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_CONTEXT_H
