#ifndef IOTYPE_H
#define IOTYPE_H

#include <QObject>

namespace duly_gui {
namespace qmlresources {
class IoTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit IoTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~IoTypeRessouce() {}
    /**
    * \brief define all the handle type by the application
    */
    enum IoType
    {
        Int,
        Float,
        Double,
        String,
        Bool,
        Object,
        Generic,
        Count //Get the size of enum, must be at the end all the time!
    };
    Q_ENUM(IoType)
};
}
}

#endif // IOTYPE_H
