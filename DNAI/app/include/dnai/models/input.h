#ifndef MODEL_INPUT_H
#define MODEL_INPUT_H

#include "dnai/models/variable.h"
#include "dnai/models/identity.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Input: public Variable, Identity, virtual public IModel
{
public:
    Input(QString const &, QString const &, QString const &, QString const &, bool, QString const &, QObject *parent = nullptr);
    virtual ~Input();

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

#endif // MODEL_INPUT_H
