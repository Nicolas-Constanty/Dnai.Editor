#ifndef CONTEXT_H
#define CONTEXT_H

#include <QQuickItem>
#include "models/context.h"

namespace duly_gui {
namespace views {
class Context : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *contextContainer READ contextContainer WRITE setContextContainer NOTIFY contextContainerChanged)
    Q_PROPERTY(QQuickItem *classContainer READ classContainer WRITE setClassContainer NOTIFY classContainerChanged)
    Q_PROPERTY(QQuickItem *functionContainer READ functionContainer WRITE setFunctionContainer NOTIFY functionContainerChanged)
    Q_PROPERTY(QQuickItem *variableContainer READ variableContainer WRITE setVariableContainer NOTIFY variableContainerChanged)

public:
    Context(const models::Context &model, QQuickItem *parent);

public:
    QQuickItem *contextContainer() const { return m_contextContainer; }
    QQuickItem *classContainer() const { return m_classContainer; }
    QQuickItem *functionContainer() const { return m_functionContainer; }
    QQuickItem *variableContainer() const { return m_variableContainer; }

public:
    void setContextContainer(QQuickItem *item);
    void setClassContainer(QQuickItem *item);
    void setFunctionContainer(QQuickItem *item);
    void setVariableContainer(QQuickItem *item);

signals:
    contextContainerChanged(QQuickItem *item);
    classContainerChanged(QQuickItem *item);
    functionContainerChanged(QQuickItem *item);
    variableContainerChanged(QQuickItem *item);

private:
    const models::Context &m_model;

protected:
    QQuickItem *m_contextContainer;
    QQuickItem *m_classContainer;
    QQuickItem *m_functionContainer;
    QQuickItem *m_variableContainer;
};
}
}

#endif // CONTEXT_H
