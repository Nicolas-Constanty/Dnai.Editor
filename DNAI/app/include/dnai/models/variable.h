#ifndef MODEL_VARIABLE_H
#define MODEL_VARIABLE_H

#include <QString>
#include <QVariant>

#include "dnai/models/common.h"
#include "dnai/models/position.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Variable: public Common, public Position, virtual public IModel
{
public:
	Variable(qint32 uid, QString const& name, QString const& description, QVector2D const& position, QString const& type,
	         bool internal, int index, int listindex, QObject* parent = nullptr);
    virtual ~Variable();

private:
    QString m_vartype;
    bool m_internal;
    //            QVariant value;

public:
    QString varType() const;
    void setVarType(const QString &type);

    bool internal() const;
    void setInternal(bool internal);


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

#endif // MODEL_VARIABLE_H
