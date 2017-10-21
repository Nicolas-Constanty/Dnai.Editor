#include "models/context.h"
#include <QJsonArray>

namespace duly_gui {
    namespace models {
        Context::Context(QString const &name, QString const &description, Context *parent)
            : Common(name, description), m_parent(parent)
        {

        }

        Context::~Context()
        {

        }

        Context *Context::parent() const
        {
            return m_parent;
        }

        void Context::setParent(Context *parent)
        {
            m_parent = parent;
        }
        
        QVector<Context*> Context::contexts() const
        {
            return m_contexts;
        }

        QVector<Class *> Context::classes() const
        {
            return m_classes;
        }
        
        QVector<Variable*> Context::variables() const
        {
            return m_variables;
        }
        
        QVector<Function*> Context::functions() const
        {
            return m_functions;
        }

        void Context::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);

            QJsonArray contexts;
            foreach (const Context *context, m_contexts) {
                QJsonObject var;
                context->serialize(var);
                contexts.append(var);
            }

            QJsonArray classes;
            foreach (const Class *classe, m_classes) {
                QJsonObject var;
                classe->serialize(var);
                contexts.append(var);
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

            obj["contexts"] = contexts;
            obj["classes"] = classes;
            obj["variables"] = variables;
            obj["functions"] = functions;
        }
    }
}
