#include <QJsonArray>
#include "models/node.h"
#include "models/function.h"

namespace duly_gui {
    namespace models {
        Node::Node(QString const &name, QString const &description, QVector2D const &position, Function *parent)
            : Common(name, description), m_parent(parent), m_position(position)
        {

        }

        Node::~Node()
        {

        }
        
        Function *Node::parent() const
        {
            return m_parent;
        }
        
        void Node::setParent(Function *parent)
        {
            m_parent = parent;
        }
        
        //        Context *Node::context() const
        //        {
        //            return m_context;
        //        }
        
        //        void Node::setContext(Context *context)
//        {
//            m_context = context;
//        }

        Function *Node::function() const
        {
            return m_function;
        }

        void Node::setFunction(Function *function)
        {
            m_function = function;
        }

        QVector2D Node::position() const
        {
            return m_position;
        }

        void Node::setPosition(const QVector2D &position)
        {
            m_position = position;
        }

        QVector<Input*> Node::inputs() const
        {
            return m_inputs;
        }

        QVector<Output*> Node::outputs() const
        {
            return m_outputs;
        }

        QVector<Flow *> Node::flows_out() const
        {
            return m_flows_out;
        }

        QVector<Flow *> Node::flows_in() const
        {
            return m_flows_in;
        }

        void Node::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);

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

            QJsonArray flows_in;
            foreach (const Flow *flow_in, m_flows_in) {
                QJsonObject var;
                flow_in->serialize(var);
                flows_in.append(var);
            }

            QJsonArray flows_out;
            foreach (const Flow *flow_out, m_flows_out) {
                QJsonObject var;
                flow_out->serialize(var);
                flows_out.append(var);
            }

            obj["position"] = QJsonObject {
                {"x", static_cast<double>(m_position.x())},
                {"y", static_cast<double>(m_position.y())}
            };
            obj["function"] = m_function->name();

            obj["inputs"] = inputs;
            obj["outputs"] = outputs;
            obj["flows_in"] = flows_in;
            obj["flows_out"] = flows_out;
        }

        IClone *Node::clone() const
        {
            return new Node(name(), description(), position(), parent());
        }
    }
}
