#ifndef IMODEL_H
#define IMODEL_H

#include <QJsonObject>
#include "dnai/models/iclone.h"

namespace dnai {
namespace models {

class IModel: virtual public IClone
{
public:
    virtual ~IModel() {}
public:
    virtual void serialize(QJsonObject &) const = 0;
    virtual void declare() const = 0;

    // IClone interface
private:
    virtual IClone *clone() const = 0;
};
}
}

#endif // IMODEL_H
