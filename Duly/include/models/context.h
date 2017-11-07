#ifndef MODEL_CONTEXT_H
#define MODEL_CONTEXT_H

#include <QVector>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/class.h"
#include "models/imodel.h"
#include "models/aregister.h"

namespace duly_gui {
    namespace views {
     class Context;
    }
    namespace models {
        class Context: public Common, public ARegister<views::Context>, virtual public IModel
        {
        public:
            Context(QString const &, QString const &, Context * = nullptr);
            virtual ~Context();

            //TODO types
        private:
            Context *m_parent;

            QVector<Context*> m_contexts;
            QVector<Class*> m_classes;
            QVector<Variable*> m_variables;
            QVector<Function*> m_functions;

        public:
            Context *parent() const;
            void setParent(Context *parent);

            QVector<Context*> contexts() const;
            QVector<Class*> classes() const;
            QVector<Variable*> variables() const;
            QVector<Function*> functions() const;

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_CONTEXT_H
