#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>

namespace dnai {
namespace model {
class Property : public QObject
{
    Q_OBJECT
public:
    Property(QObject *parent = nullptr);
    virtual ~Property();
};
}
}

#endif // PROPERTY_H
