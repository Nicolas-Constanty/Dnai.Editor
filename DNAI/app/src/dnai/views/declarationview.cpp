#include "dnai/views/declarationview.h"
#include "dnai/app.h"

namespace dnai
{
	namespace views
	{
        DeclarationView::DeclarationView(QQuickItem* parent) : ContextView(parent)
        {
		}

        DeclarationView::DeclarationView(const QString& path, QQuickItem* parent) : ContextView(path, parent)
		{
		}

		dnai::models::DeclarationModel* DeclarationView::contextModel() const
		{
			return dynamic_cast<dnai::models::DeclarationModel*>(getModel("contextModel"));
		}

		void DeclarationView::setContextModel(dnai::models::DeclarationModel* model)
		{
			if (contextModel() == model)
				return;
			addModel(static_cast<QObject*>(model), "contextModel");
			contextModelChanged(model);
		}
	}
}
