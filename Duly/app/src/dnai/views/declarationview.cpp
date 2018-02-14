#include "dnai/views/declarationview.h"

namespace dnai
{
	namespace views
	{
		DeclarationView::DeclarationView(QObject* parent) : ContextView(parent)
		{
		}

		DeclarationView::DeclarationView(const QString& path, QObject* parent) : ContextView(path, parent)
		{
		}

		dnai::models::DeclarationModel* DeclarationView::contextModel() const
		{
			return dynamic_cast<dnai::models::DeclarationModel*>(getModel("contextModel"));
		}

		void DeclarationView::setContextModel(dnai::models::DeclarationModel* model)
		{
			addModel(static_cast<QObject*>(model), "contextModel");
		}
	}
}
