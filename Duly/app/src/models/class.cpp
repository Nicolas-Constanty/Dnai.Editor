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
        
        QList<Variable*> Class::attributes() const
        {
            return m_attributes;
        }
        
        QList<Function*> Class::methods() const
        {
            return m_methods;
        }
        
        QList<Function*> Class::functions() const
        {
            return m_functions;
        }

        QList<Class*> Class::classes() const
        {
            return m_classes;
        }

        void Class::addAttribute(Variable *model)
        {
            m_attributes.push_back(model);
        }

        void Class::addMethod(Function *model)
        {
            m_methods.push_back(model);
        }

        void Class::addFunction(Function *model)
        {
            m_functions.push_back(model);
        }

        void Class::addClass(Class *model)
        {
            m_classes.push_back(model);
        }

        void Class::removeAttribute(Variable *model)
        {
            m_attributes.removeOne(model);
        }

        void Class::removeMethod(Function *model)
        {
            m_methods.removeOne(model);
        }

        void Class::removeFunction(Function *model)
        {
            m_functions.removeOne(model);
        }

        void Class::removeClass(Class *model)
        {
            m_classes.removeOne(model);
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

            QJsonArray functions;
            foreach (const Function *function, m_functions) {
                QJsonObject var;
                function->serialize(var);
                functions.append(var);
            }

            QJsonArray classes;
            foreach (const Class *classe, m_classes) {
                QJsonObject var;
                classe->serialize(var);
                classes.append(var);
            }

            obj["attributes"] = attributes;
            obj["methods"] = methods;
            obj["functions"] = functions;
            obj["classes"] = functions;
        }

        IClone *Class::clone() const
        {
            return new Class(name(), description());
        }
    }
}
