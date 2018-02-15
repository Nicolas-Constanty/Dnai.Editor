#include <QJsonArray>
#include <QDebug>

#include "dnai/models/context.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai {
    namespace models {
        Context::Context(QString const &uid, QString const &name, QString const &description, QVector2D const &position, int index, int listindex, QObject *parent)
            : Common(uid, name, description, index, listindex, parent), Position(position)
        {
            m_type = ModelTypes::Context;
        }

        Context::~Context()
        {

        }
        
        QList<Context*> Context::contexts() const
        {
            return m_contexts;
        }

        QList<Class *> Context::classes() const
        {
            return m_classes;
        }
        
        QList<Variable*> Context::variables() const
        {
            return m_variables;
        }
        
        QList<Function*> Context::functions() const
        {
            return m_functions;
        }

        void Context::addContext(Context *model)
        {
            m_contexts.push_back(model);
        }

        void Context::addClass(Class *model)
        {
            m_classes.push_back(model);
        }

        void Context::addVariable(Variable *model)
        {
            m_variables.push_back(model);
        }

        void Context::addFunction(Function *model)
        {
            m_functions.push_back(model);
        }

        void Context::removeContext(Context *model)
        {
            m_contexts.removeOne(model);
        }

        void Context::removeClass(Class *model)
        {
            m_classes.removeOne(model);
        }

        void Context::removeVariable(Variable *model)
        {
            m_variables.removeOne(model);
        }

        void Context::removeFunction(Function *model)
        {
            m_functions.removeOne(model);
        }

        void Context::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            Position::serialize(obj);

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

        void Context::declare() const
        {
            controllers::ClientController::shared().sendDeclareEvent(PackageDataCom::ENTITYCORE::CONTEXT_D, 0, name(), PackageDataCom::VISIBILITYCORE::PUBLIC);
        }

        IClone *Context::clone() const
        {
            return new Context(uid(), name(), description(), position(), index(), listIndex());
        }
    }
}
