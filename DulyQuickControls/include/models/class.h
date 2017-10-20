#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <QVector>
#include "models/common.h"
#include "models/variable.h"
#include "models/function.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Class: public Common, virtual public IModel
        {
        public:
            Class(QString const &, QString const &);
            virtual ~Class();

        private:
            QVector<Variable*> m_attributes;
            QVector<Function*> m_methods;
            QVector<Variable*> m_variables;
            QVector<Function*> m_functions;

        public:
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
