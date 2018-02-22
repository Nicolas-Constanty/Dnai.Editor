#ifndef MODEL_FLOW_H
#define MODEL_FLOW_H

#include "dnai/models/identity.h"
#include "dnai/models/imodel.h"
#include "dnai/models/common.h"

namespace dnai {
namespace models {
class Flow: public Common, public Identity, virtual public IModel
{
public:
    Flow(const qint32 uid, QString const &name, QString const &description, QString const &linked_uid, QObject *parent = nullptr);
    virtual ~Flow();

    // IModel interface
public:
    virtual void serialize(QJsonObject &) const;
    virtual void declare() const;

    // IClone interface
private:
    IClone *clone() const;
};
}
}

#endif // MODEL_FLOW_H
