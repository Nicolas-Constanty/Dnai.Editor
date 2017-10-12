#ifndef ISCALABLE_H
#define ISCALABLE_H

#include <QPointF>

class IScalable
{
public:
    virtual qreal scaleFactor() const = 0;
    virtual QPointF scalePos() const = 0;
    virtual QPointF realPos() const = 0;
};


#endif // ISCALABLE_H
