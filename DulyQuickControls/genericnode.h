#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <QQuickItem>
#include "observablelist.h"
#include "roundedrectangle.h"
#include "input.h"
#include "output.h"

class GenericNode : public RoundedRectangle
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    GenericNode(QQuickItem *parent);

    QColor backgroundColor() const { return m_backgroundColor; }
    void setBackgroundColor(const QColor & color);


signals:
    void backgroundColorChanged(const QColor &color);

private:
    QColor m_backgroundColor;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

    ObservableList<Input *> m_inputs;
    ObservableList<Output *> m_outputs;
};

#endif // GENERICNODE_H
