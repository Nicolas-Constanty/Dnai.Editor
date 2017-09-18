#ifndef GRAPHICSLINE_H
#define GRAPHICSLINE_H

#include "anode.h"
#include <QPen>
#include <QGraphicsLineItem>

class GraphicsLine : public QGraphicsLineItem
{
public:
    GraphicsLine(AInput *p1, AInput *p2);

public:
    void display();

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    AInput *m_p1;
    AInput *m_p2;
    QPen    m_pen;
};

#endif // GRAPHICSLINE_H
