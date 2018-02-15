#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <QList>
#include <QVector2D>
#include "dnai/models/common.h"
#include "dnai/models/input.h"
#include "dnai/models/output.h"
#include "dnai/models/flow.h"
#include "dnai/models/imodel.h"
#include "dnai/models/position.h"

namespace dnai {
namespace models {
class Function;
class Node: public Common, public Position, virtual public IModel
{
public:
    Node(QString const &, QString const &, QString const &, QVector2D const &, Function * = nullptr, QObject * = nullptr);
    virtual ~Node();

private:
    Function *m_function;
    QList<Input*> m_inputs;
    QList<Output*> m_outputs;
    QList<Flow*> m_flows_in;
    QList<Flow*> m_flows_out;

public:
    Function *function() const;
    void setFunction(Function *function);
    QList<Input*> inputs() const;
    QList<Output*> outputs() const;
    QList<Flow *> flows_in() const;
    QList<Flow *> flows_out() const;

public:
    void addInput(Input *);
    void addOutput(Output *);
    void addFlowIn(Flow *);
    void addFlowOut(Flow *);

public:
    void removeInput(Input *);
    void removeOutput(Output *);
    void removeFlowIn(Flow *);
    void removeFlowOut(Flow *);

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

#endif // MODEL_NODE_H
