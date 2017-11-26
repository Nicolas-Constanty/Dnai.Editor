#ifndef CONTEXT_H
#define CONTEXT_H

#include <QQuickItem>
#include "views/declarationview.h"
#include "models/context.h"

namespace duly_gui {
namespace views {
class Context : public DeclarationView
{
    Q_OBJECT
public:
	explicit Context(QQuickItem *parent);
	Context(models::Context* model, QQuickItem* parent);

private:
    models::Context *m_model;
};
}
}

#endif // CONTEXT_H
