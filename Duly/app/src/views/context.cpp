#include "views/context.h"
#include "dulyapp.h"

namespace duly_gui {
namespace views {
Context::Context(QQuickItem *parent) :
    DeclarationView(parent),
    m_model(nullptr)
{
    setType(DeclarationTypeRessouce::DeclarationType::Context);
	
//	const auto declView = static_cast<DulyApp *>(DulyApp::instance())->settings()->style()->declarationView();
	/*auto v = view();
	v->setRadius(declView->declContext()->radius());
	v->setFillColor(declView->declContext()->background());
	v->setBorderColor(declView->declContext()->border()->color());
	v->setBorderWidth(declView->declContext()->border()->width());
	v->setWidth(declView->itemSize());
	v->setHeight(declView->itemSize());
	v->setAntialiasing(true);*/
}
Context::Context(models::Context *model, QQuickItem *parent) :
	DeclarationView(parent),
    m_model(model)
{
    setType(DeclarationTypeRessouce::DeclarationType::Context);
}
}
}
