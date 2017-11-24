#ifndef MODEL_CONTEXT_H
#define MODEL_CONTEXT_H

#include <QList>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/class.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Context: public Common, virtual public IModel
        {
        public:
            Context(QString const &, QString const &, QObject * = nullptr);
            virtual ~Context();

            //TODO types
            QList<Context*> m_contexts;
            QList<Class*> m_classes;
            QList<Variable*> m_variables;
            QList<Function*> m_functions;

        public:
            QList<Context*> contexts() const;
            QList<Class*> classes() const;
            QList<Variable*> variables() const;
            QList<Function*> functions() const;

        public:
            void addContext(Context *);
            void addClass(Class *);
            void addVariable(Variable *);
            void addFunction(Function *);

        public:
            void removeContext(Context *);
            void removeClass(Class *);
            void removeVariable(Variable *);
            void removeFunction(Function *);

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_CONTEXT_H
