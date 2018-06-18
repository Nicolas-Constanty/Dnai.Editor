#ifndef DECLARATIONVIEW_H
#define DECLARATIONVIEW_H

#include "contextview.h"
#include "dnai/models/entity.h"

namespace dnai
{
	namespace views
	{
		class DeclarationView : public ContextView
		{
			Q_OBJECT
            Q_PROPERTY(dnai::models::Entity *contextModel READ contextModel WRITE setContextModel NOTIFY contextModelChanged)
		public:
            explicit DeclarationView(QQuickItem *parent = nullptr);

        signals:
            void contextModelChanged(dnai::models::Entity *model);

        public:
            dnai::models::Entity *contextModel() const;
            void setContextModel(dnai::models::Entity *model);
		};
	}
}
#endif // DECLARATIONVIEW_H
