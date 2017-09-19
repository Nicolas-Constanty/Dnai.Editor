#ifndef AINPUT_H
#define AINPUT_H

#include <QGraphicsEllipseItem>

class ANode;

class AInput : public QGraphicsRectItem
{
public:
    AInput(int x, int y, int width, int height, QGraphicsItem *, ANode *);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    ANode   *m_node;
    bool    m_origin;

public:
    void addLine(QGraphicsLineItem *line, bool isPoint1) {
         this->line = line;
         isP1 = isPoint1;
     }

 public:
     QGraphicsLineItem *line;
     bool isP1;
};

#endif // AINPUT_H
