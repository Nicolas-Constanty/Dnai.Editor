#include "models/function.h"
#include <QJsonArray>

namespace duly_gui {
    namespace models {
        Function::Function(QString const &uid, QString const &name, QString const &description, QObject *parent)
            : Common(uid, name, description, parent)
        {

        }

        Function::~Function()
        {

        }
        
        QList<Variable*> Function::variables() const
        {
            return m_variables;
        }
        
        QList<Input*> Function::inputs() const
        {
            return m_inputs;
        }

        QList<Output*> Function::outputs() const
        {
            return m_outputs;
        }

        QList<Node*> Function::nodes() const
        {
            return m_nodes;
        }

        void Function::addVariable(Variable *model)
        {
            m_variables.push_back(model);
        }

        void Function::addInput(Input *model)
        {
            m_inputs.push_back(model);
        }

        void Function::addOutput(Output *model)
        {
            m_outputs.push_back(model);
        }

        void Function::addNode(Node *model)
        {
            m_nodes.push_back(model);
        }

        void Function::removeVariable(Variable *model)
        {
            m_variables.removeOne(model);
        }

        void Function::removeInput(Input *model)
        {
            m_inputs.removeOne(model);
        }

        void Function::removeOutput(Output *model)
        {
            m_outputs.removeOne(model);
        }

        void Function::removeNode(Node *model)
        {
            m_nodes.removeOne(model);
        }

        void Function::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);

            QJsonArray variables;
            foreach (const Variable *variable, m_variables) {
                QJsonObject var;
                variable->serialize(var);
                variables.append(var);
            }

            QJsonArray inputs;
            foreach (const Input *input, m_inputs) {
                QJsonObject var;
                input->serialize(var);
                inputs.append(var);
            }

            QJsonArray outputs;
            foreach (const Output *output, m_outputs) {
                QJsonObject var;
                output->serialize(var);
                outputs.append(var);
            }

            QJsonArray nodes;
            foreach (const Node *node, m_nodes) {
                QJsonObject var;
                node->serialize(var);
                nodes.append(var);
            }

            obj["variables"] = variables;
            obj["inputs"] = inputs;
            obj["outputs"] = outputs;
            obj["nodes"] = nodes;
        }

        IClone *Function::clone() const
        {
            return new Function(uid(), name(), description());
        }
    }
}
