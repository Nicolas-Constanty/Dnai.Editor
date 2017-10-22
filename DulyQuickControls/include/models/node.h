#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <QVector>
#include <QVector2D>
#include "models/common.h"
#include "models/input.h"
#include "models/output.h"
#include "models/flow.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
    class Context;
    class Function;
        class Node: public Common, virtual public IModel
        {
        public:
            Node(QString const &, QString const &, QVector2D const &, Function * = nullptr);
            virtual ~Node();

        private:
            Function *m_parent;
//            Context *m_context;
            Function *m_function;
            QVector2D m_position;
            QVector<Input*> m_inputs;
            QVector<Output*> m_outputs;
            QVector<Flow*> m_flows_in;
            QVector<Flow*> m_flows_out;

        public:
            Function *parent() const;
            void setParent(Function *parent);
//            Context *context() const;
//            void setContext(Context *context);
            Function *function() const;
            void setFunction(Function *function);
            QVector2D position() const;
            void setPosition(const QVector2D &position);
            QVector<Input*> inputs() const;
            QVector<Output*> outputs() const;
            QVector<Flow *> flows_in() const;
            QVector<Flow *> flows_out() const;

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_NODE_H
