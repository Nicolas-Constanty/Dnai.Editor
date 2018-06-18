#include "border.h"

Border::Border(QObject *parent) : QObject(parent), m_rect(0,0,0,0), m_color(0,0,0)
{
}

void Border::setColor(const QColor &c)
{
    m_color = c;
}

void Border::setRect(const QVector4D &r)
{
    m_rect = r;
}

const QColor &Border::color() const
{
    return m_color;
}

const QVector4D &Border::rect() const
{
    return m_rect;
}
