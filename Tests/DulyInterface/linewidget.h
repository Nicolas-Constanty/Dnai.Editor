#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>
#include <QObject>
#include <QPainter>

class LineWidget : public QWidget
{
public:
    LineWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
        painter.drawLine(0, 0, 200, 200);
    }
};
#endif // LINEWIDGET_H
