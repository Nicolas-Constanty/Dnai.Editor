#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <QList>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Class: public Common, virtual public IModel
        {
        public:
            Class(QString const &, QString const &, Context * = nullptr);
            virtual ~Class();

        private:
            Context *m_parent;

            QList<Variable*> m_attributes;
            QList<Function*> m_methods;
            QList<Function*> m_functions;
            QList<Class*> m_classes;
            //TODO add position

        public:
            Context *parent() const;
            void setParent(Context *parent);

            QList<Variable*> attributes() const;
            QList<Function*> methods() const;
            QList<Function*> functions() const;
            QList<Class*> classes() const;

        public:
            void addAttribute(Variable *);
            void addMethod(Function *);
            void addFunction(Function *);
            void addClass(Class *);

        public:
            void removeAttribute(Variable *);
            void removeMethod(Function *);
            void removeFunction(Function *);
            void removeClass(Class *);

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}


#endif // MODEL_CLASS_H
