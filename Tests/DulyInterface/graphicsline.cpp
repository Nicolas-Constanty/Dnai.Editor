#include "graphicsline.h"
#include "ainput.h"

GraphicsLine::GraphicsLine(AInput *p1, AInput *p2)
    : QGraphicsLineItem(),
      m_p1(p1),
      m_p2(p2)
{
    m_pen = QPen(Qt::green, 9, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
    setPen(m_pen);
    setAcceptHoverEvents(true);

}

void GraphicsLine::display() {
    m_p1->addLine(this, true);
    m_p2->addLine(this, false);
}

void GraphicsLine::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    m_pen.setColor(Qt::red);
    setPen(m_pen);
}

void GraphicsLine::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    m_pen.setColor(Qt::green);
    setPen(m_pen);
}
