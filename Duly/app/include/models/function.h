#ifndef MODEL_FUNCTION_H
#define MODEL_FUNCTION_H

#include <QList>
#include "models/common.h"
#include "models/variable.h"
#include "models/input.h"
#include "models/output.h"
#include "models/node.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Function: public Common, virtual public IModel
        {
        public:
            Function(QString const &, QString const &, Context * = nullptr);
            virtual ~Function();

        private:
            Context *m_parent;

            QList<Variable*> m_variables;
            QList<Input*> m_inputs;
            QList<Output*> m_outputs;
            QList<Node*> m_nodes;

        public:
            Context *parent() const;
            void setParent(Context *parent);

            QList<Variable*> variables() const;
            QList<Input*> inputs() const;
            QList<Output*> outputs() const;
            QList<Node*> nodes() const;

        public:
            void addVariable(Variable *);
            void addInput(Input *);
            void addOutput(Output *);
            void addNode(Node *);

        public:
            void removeVariable(Variable *);
            void removeInput(Input *);
            void removeOutput(Output *);
            void removeNode(Node *);

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_FUNCTION_H
