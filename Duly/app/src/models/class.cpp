#include "models/class.h"
#include <QJsonArray>

namespace duly_gui {
    namespace models {
        Class::Class(QString const &name, QString const &description, Context *parent)
            : Common(name, description), m_parent(parent)
        {

        }

        Class::~Class()
        {

        }
        
        Context *Class::parent() const
        {
            return m_parent;
        }
        
        void Class::setParent(Context *parent)
        {
            m_parent = parent;
        }
        
        QVector<Variable*> Class::attributes() const
        {
            return m_attributes;
        }
        
        QVector<Function*> Class::methods() const
        {
            return m_methods;
        }
        
        QVector<Variable*> Class::variables() const
        {
            return m_variables;
        }
        
        QVector<Function*> Class::functions() const
        {
            return m_functions;
        }

        void Class::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);

            QJsonArray attributes;
            foreach (const Variable *attribute, m_attributes) {
                QJsonObject var;
                attribute->serialize(var);
                attributes.append(var);
            }

            QJsonArray methods;
            foreach (const Function *method, m_methods) {
                QJsonObject var;
                method->serialize(var);
                methods.append(var);
            }

            QJsonArray variables;
            foreach (const Variable *variable, m_variables) {
                QJsonObject var;
                variable->serialize(var);
                variables.append(var);
            }

            QJsonArray functions;
            foreach (const Function *function, m_functions) {
                QJsonObject var;
                function->serialize(var);
                functions.append(var);
            }

            obj["attributes"] = attributes;
            obj["methods"] = methods;
            obj["variables"] = variables;
            obj["functions"] = functions;
        }

        IClone *Class::clone() const
        {
            return new Class(name(), description(), parent());
        }
    }
}
