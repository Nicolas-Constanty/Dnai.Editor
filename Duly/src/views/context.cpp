#include "views/context.h"

namespace duly_gui {
namespace views {
Context::Context(const models::Context &model, QQuickItem *parent) :
    QQuickItem(parent),
    m_model(model)
{
}

void Context::setContextContainer(QQuickItem *item)
{
    if (item == m_contextContainer)
        return;
    m_contextContainer = item;
    update();
}
void Context::setClassContainer(QQuickItem *item)
{
    if (item == m_classContainer)
        return;
    m_classContainer = item;
    update();
}
void Context::setFunctionContainer(QQuickItem *item)
{
    if (item == m_functionContainer)
        return;
    m_functionContainer = item;
    update();
}
void Context::setVariableContainer(QQuickItem *item)
{
    if (item == m_variableContainer)
        return;
    m_variableContainer = item;
    update();
}
}
}
