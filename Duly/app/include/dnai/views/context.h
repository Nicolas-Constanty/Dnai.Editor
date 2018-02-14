#ifndef CONTEXT_H
#define CONTEXT_H

#include <QQuickItem>

#include "dnai/views/declarationview.h"
#include "dnai/models/context.h"

namespace dnai {
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
