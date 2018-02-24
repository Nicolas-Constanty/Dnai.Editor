#ifndef IMODEL_H
#define IMODEL_H

#include <list>
#include <QList>
#include <QJsonObject>
#include "dnai/models/iclone.h"

namespace dnai {
namespace models {

class IModel: virtual public IClone
{
public:
	virtual ~IModel() = default;
public:
    virtual void serialize(QJsonObject &) const = 0;
    virtual void declare() const = 0;
	virtual const QList<QString> &editableProperties() = 0;

    // IClone interface
private:
	IClone *clone() const override = 0;
};
}
}

#endif // IMODEL_H
