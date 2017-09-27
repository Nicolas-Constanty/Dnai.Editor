#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <QQuickItem>
#include "qnanoquickitem.h"
#include "observablelist.h"
#include "roundedrectangle.h"
#include "input.h"
#include "output.h"

class GenericNode : public QNanoQuickItem
{
	Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
	GenericNode(QQuickItem *parent = nullptr);

	// Reimplement
	QNanoQuickItemPainter *createItemPainter() const override;

    QColor backgroundColor() const { return m_backgroundColor; }
    void setBackgroundColor(const QColor & color);

	double radius() const { return m_radius; }
    void setRadius(double radius);



signals:
    void backgroundColorChanged(const QColor &color);
    void radiusChanged(double r);

private:
    QColor m_backgroundColor;

    ObservableList<Input *> m_inputs;
    ObservableList<Output *> m_outputs;
    double m_radius;
};

#endif // GENERICNODE_H
