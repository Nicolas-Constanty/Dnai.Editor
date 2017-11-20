#include "models/function.h"
#include <QJsonArray>

namespace duly_gui {
    namespace models {
        Function::Function(QString const &name, QString const &description, Context *parent)
            : Common(name, description), m_parent(parent)
        {

        }

        Function::~Function()
        {

        }
        
        Context *Function::parent() const
        {
            return m_parent;
        }
        
        void Function::setParent(Context *parent)
        {
            m_parent = parent;
        }
        
        QVector<Variable*> Function::variables() const
        {
            return m_variables;
        }
        
        QVector<Input*> Function::inputs() const
        {
            return m_inputs;
        }

        QVector<Output*> Function::outputs() const
        {
            return m_outputs;
        }

        QVector<Node*> Function::nodes() const
        {
            return m_nodes;
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
            return new Function(name(), description(), parent());
        }
    }
}
