#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <QVector>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace views {
        class Class;
    }
    namespace models {
        class Class: public Common, virtual public IModel
        {
        public:
            Class(QString const &, QString const &, Context * = nullptr);
            virtual ~Class();

        private:
            Context *m_parent;

            QVector<Variable*> m_attributes;
            QVector<Function*> m_methods;
            QVector<Variable*> m_variables;
            QVector<Function*> m_functions;

        public:
            Context *parent() const;
            void setParent(Context *parent);

            QVector<Variable*> attributes() const;
            QVector<Function*> methods() const;
            QVector<Variable*> variables() const;
            QVector<Function*> functions() const;

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}


#endif // MODEL_CLASS_H
