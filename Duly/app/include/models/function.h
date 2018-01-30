#ifndef MODEL_FUNCTION_H
#define MODEL_FUNCTION_H

#include <QList>
#include "models/common.h"
#include "models/variable.h"
#include "models/input.h"
#include "models/output.h"
#include "models/node.h"
#include "models/position.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Function: public Common, public Position, virtual public IModel
        {
        public:
            Function(QString const &, QString const &, QString const &, QVector2D const &, int list, int listindex, QObject * = nullptr);
            virtual ~Function();

        private:
            QList<Variable*> m_variables;
            QList<Input*> m_inputs;
            QList<Output*> m_outputs;
            QList<Node*> m_nodes;

        public:
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
            virtual void declare() const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_FUNCTION_H
