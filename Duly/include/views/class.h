#ifndef VIEWS_CLASS_H
#define VIEWS_CLASS_H

#include <QQuickItem>
#include "models/class.h"

namespace duly_gui {
namespace views {
class Class : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *classContainer READ classContainer WRITE setClassContainer NOTIFY classContainerChanged)
    Q_PROPERTY(QQuickItem *functionContainer READ functionContainer WRITE setFunctionContainer NOTIFY functionContainerChanged)
    Q_PROPERTY(QQuickItem *variableContainer READ variableContainer WRITE setVariableContainer NOTIFY variableContainerChanged)

public:
    Class(const models::Class &model, QQuickItem *parent);

public:
    QQuickItem *classContainer() const { return m_classContainer; }
    QQuickItem *functionContainer() const { return m_functionContainer; }
    QQuickItem *variableContainer() const { return m_variableContainer; }

public:
    void setClassContainer(QQuickItem *item);
    void setFunctionContainer(QQuickItem *item);
    void setVariableContainer(QQuickItem *item);

signals:
    classContainerChanged(QQuickItem *item);
    functionContainerChanged(QQuickItem *item);
    variableContainerChanged(QQuickItem *item);

private:
    const models::Class &m_model;

protected:
    QQuickItem *m_classContainer;
    QQuickItem *m_functionContainer;
    QQuickItem *m_variableContainer;
};
}
}

#endif // VIEWS_CLASS_H
