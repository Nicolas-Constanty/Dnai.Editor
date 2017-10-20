#ifndef MODEL_CONTEXT_H
#define MODEL_CONTEXT_H

#include <QVector>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Context: public Common, virtual public IModel
        {
        public:
            Context(QString const &, QString const &);
            virtual ~Context();

            //TODO types
        private:
            QVector<Context*> m_contexts;
            QVector<Variable*> m_variables;
            QVector<Function*> m_functions;

        public:
            QVector<Context*> contexts() const;
            QVector<Variable*> variables() const;
            QVector<Function*> functions() const;

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_CONTEXT_H
