#include "models/context.h"
#include <QJsonArray>

namespace duly_gui {
    namespace models {
        Context::Context(QString const &name, QString const &description)
            : Common(name, description)
        {

        }

        Context::~Context()
        {

        }
        
        QVector<Variable*> Context::variables() const
        {
            return m_variables;
        }
        
        QVector<Function*> Context::functions() const
        {
            return m_functions;
        }
        
        QVector<Context*> Context::contexts() const
        {
            return m_contexts;
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
            obj["variables"] = variables;
            obj["functions"] = functions;
        }
    }
}
