#include "dnai/app.h"
#include "dnai/views/declarationview.h"

namespace dnai
{
	namespace views
	{
        DeclarationView::DeclarationView(QQuickItem* parent) : ContextView("qrc:/resources/Components/DeclarationView.qml", parent)
        {
		}

        dnai::models::Entity* DeclarationView::contextModel() const
		{
            return dynamic_cast<dnai::models::Entity*>(getModel("contextModel"));
		}

        void DeclarationView::setContextModel(dnai::models::Entity* model)
		{
			if (contextModel() == model)
				return;
            addModel(static_cast<QObject*>(model), "contextModel");
            contextModelChanged(model);
		}
	}
}
