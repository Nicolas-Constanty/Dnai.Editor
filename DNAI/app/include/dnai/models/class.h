#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <QList>

#include "dnai/models/common.h"
#include "dnai/models/variable.h"
#include "dnai/models/function.h"
#include "dnai/models/position.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Class: public Common, public Position, virtual public IModel
{
public:
    Class(qint32 uid, QString const &name, QString const &description, QVector2D const &position, int index, int listindex, QObject *parent = nullptr);
    virtual ~Class();

private:
    QList<Variable*> m_attributes;
    QList<Function*> m_methods;
    QList<Function*> m_functions;
    QList<Class*> m_classes;
    //TODO add position

public:
    QList<Variable*> attributes() const;
    QList<Function*> methods() const;
    QList<Function*> functions() const;
    QList<Class*> classes() const;

public:
    void addAttribute(Variable *);
    void addMethod(Function *);
    void addFunction(Function *);
    void addClass(Class *);

public:
    void removeAttribute(Variable *);
    void removeMethod(Function *);
    void removeFunction(Function *);
    void removeClass(Class *);

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


#endif // MODEL_CLASS_H
