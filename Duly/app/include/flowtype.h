#ifndef FLOWTYPE_H
#define FLOWTYPE_H

#include <QObject>

class FlowTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit FlowTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~FlowTypeRessouce() {}

    enum FlowType
    {
        Enter,
        Exit
    };
    Q_ENUM(FlowType)
};

#endif // FLOWTYPE_H
