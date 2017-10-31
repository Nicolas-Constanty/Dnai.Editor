#include "models/node.h"

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
        }
    }
}
