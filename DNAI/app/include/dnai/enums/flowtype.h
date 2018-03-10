#ifndef FLOWTYPE_H
#define FLOWTYPE_H

#include <QObject>

namespace dnai {
namespace enums {
class FlowTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit FlowTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~FlowTypeRessouce() {}

	/**
     * \brief Enum of available type for a flow
     */
    enum FlowType
    {
        Enter,
        Exit
    };
    Q_ENUM(FlowType)
};
}
}

#endif // FLOWTYPE_H
