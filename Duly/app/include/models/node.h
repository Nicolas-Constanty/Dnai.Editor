#ifndef MODEL_NODE_H
#define MODEL_NODE_H

#include <QList>
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
            QList<Input*> m_inputs;
            QList<Output*> m_outputs;
            QList<Flow*> m_flows_in;
            QList<Flow*> m_flows_out;

        public:
            Function *parent() const;
            void setParent(Function *parent);
//            Context *context() const;
//            void setContext(Context *context);
            Function *function() const;
            void setFunction(Function *function);
            QVector2D position() const;
            void setPosition(const QVector2D &position);
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

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_NODE_H
