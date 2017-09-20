#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <QQuickItem>

class GenericNode : public QQuickItem
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
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
};

#endif // GENERICNODE_H
