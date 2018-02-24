#ifndef MODEL_CONTEXT_H
#define MODEL_CONTEXT_H

#include "dnai/models/common.h"
#include "dnai/models/variable.h"
#include "dnai/models/function.h"
#include "dnai/models/class.h"
#include "dnai/models/position.h"
#include "dnai/models/imodel.h"

namespace dnai {
namespace models {
class Context: public Common, public Position, virtual public IModel
{
public:
    Context(qint32 uid, QString const &name, QString const &description, QVector2D const &position, int index, int listindex, QObject *parent = nullptr);
    virtual ~Context();

    //TODO types
    QList<Context*> m_contexts;
    QList<Class*> m_classes;
    QList<Variable*> m_variables;
    QList<Function*> m_functions;

public:
    QList<Context*> contexts() const;
    QList<Class*> classes() const;
    QList<Variable*> variables() const;
    QList<Function*> functions() const;

public:
    void addContext(Context *);
    void addClass(Class *);
    void addVariable(Variable *);
    void addFunction(Function *);

public:
    void removeContext(Context *);
    void removeClass(Class *);
    void removeVariable(Variable *);
    void removeFunction(Function *);

    // IModel interface
public:
	void serialize(QJsonObject &) const override;
	void declare() const override;
	const QList<QString>& editableProperties() override;

    // IClone interface
private:
    IClone *clone() const override;
	static QList<QString> m_editableProperties;
public:
};
}
}

#endif // MODEL_CONTEXT_H
