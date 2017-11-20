#ifndef MODEL_FUNCTION_H
#define MODEL_FUNCTION_H

#include <QVector>
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

            QVector<Variable*> m_variables;
            QVector<Input*> m_inputs;
            QVector<Output*> m_outputs;
            QVector<Node*> m_nodes;

        public:
            Context *parent() const;
            void setParent(Context *parent);

            QVector<Variable*> variables() const;
            QVector<Input*> inputs() const;
            QVector<Output*> outputs() const;
            QVector<Node*> nodes() const;

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
