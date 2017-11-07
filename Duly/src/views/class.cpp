#include "views/class.h"

namespace duly_gui {
namespace views {
Class::Class(const models::Class &model, QQuickItem *parent) :
    QQuickItem(parent),
    m_model(model)
{
}

void Class::setClassContainer(QQuickItem *item)
{
    if (item == m_classContainer)
        return;
    m_classContainer = item;
    emit classContainerChanged(item);
    update();
}
void Class::setFunctionContainer(QQuickItem *item)
{
    if (item == m_functionContainer)
        return;
    m_functionContainer = item;
    emit functionContainerChanged(item);
    update();
}
void Class::setVariableContainer(QQuickItem *item)
{
    if (item == m_variableContainer)
        return;
    m_variableContainer = item;
    emit variableContainerChanged(item);
    update();
}
}
}
