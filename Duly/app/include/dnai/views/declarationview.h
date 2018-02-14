#ifndef DECLARATIONVIEW_H
#define DECLARATIONVIEW_H

#include "contextview.h"
#include "dnai/models/declarationmodel.h"

namespace dnai
{
	namespace views
	{
		class DeclarationView : public ContextView
		{
			Q_OBJECT
            Q_PROPERTY(dnai::models::DeclarationModel *contextModel READ contextModel WRITE setContextModel NOTIFY contextModelChanged)
		public:
			explicit DeclarationView(QObject *parent = nullptr);
			explicit DeclarationView(const QString &path, QObject *parent = nullptr);

        signals:
            void contextModelChanged(dnai::models::DeclarationModel *model);

        public:
            dnai::models::DeclarationModel *contextModel() const;
            void setContextModel(dnai::models::DeclarationModel *model);
		};
	}
}
#endif // DECLARATIONVIEW_H
