#include <functional>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "core.h"

#include "dnai/core/variablehandler.h"
#include "dnai/commands/corecommand.h"
#include "dnai/models/gui/declarable/variable.h"

#include "dnai/commands/commandmanager.h"

#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        VariableHandler::VariableHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void VariableHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));

            ::core::variable::onTypeSet(std::bind(&VariableHandler::onTypeSet, this, _1, _2));
            ::core::variable::onSetTypeError(std::bind(&VariableHandler::onSetTypeError, this, _1, _2, _3));
            ::core::variable::onValueSet(std::bind(&VariableHandler::onValueSet, this, _1, _2));
            ::core::variable::onSetValueError(std::bind(&VariableHandler::onSetValueError, this, _1, _2, _3));
        }

        void VariableHandler::onEntityAdded(::core::EntityID id, models::Entity &entity)
        {
            Q_UNUSED(entity)
            models::gui::declarable::Variable *var = getVariableData(id);

            if (var != nullptr)
            {
                //todo: add a system to save action into a map in order to execute it once done

                qDebug() << "Entity added";
                if (var->varType() != ::core::UNDEFINED_ID) {}
                    setType(id, var->varType());
                if (!var->value().isEmpty())
                    setValue(id, var->value());
            }
        }

        void VariableHandler::setType(quint32 var, quint32 typ)
        {
            qDebug() << "Set " << var << " type " << typ;

            models::Entity &variable = manager.getEntity(var);
            ::core::EntityID oldType = getVariableData(variable.id(), true)->varType();

            if (manager.contains(typ))
            {
                models::Entity &type = manager.getEntity(typ);

                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Variable.SetType", true,
                        /*
                         * Execute
                         */
                        [&variable, &type]() {
                            ::core::variable::setType(variable.id(), type.id());
                        },
                        /*
                         * Un-execute
                         */
                        [oldType, &variable]() {
                            ::core::variable::setType(variable.id(), oldType);
                        }));
            }

            if (typ >= 1 && typ <= 5)
            {
                qDebug() << "Set scalar type";
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Variable.SetType", true,
                        std::bind(&::core::variable::setType, variable.id(), typ),
                        std::bind(&::core::variable::setType, variable.id(), oldType)));
            }
        }

        void VariableHandler::setValue(quint32 var, const QString &value)
        {
            models::Entity &variable = manager.getEntity(var);
            QString oldval = getVariableData(variable.id(), true)->value();

            qDebug() << "set " << var << " value to " << value;
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Variable.SetValue", true,
                    /*
                     * Execute
                     */
                    [&variable, value]() {
                      ::core::variable::setValue(variable.id(), value);
                    },
                    /*
                     * Un-execute
                     */
                    [&variable, oldval]() {
                      ::core::variable::setValue(variable.id(), oldval);
                    }));
        }

        models::gui::declarable::Variable   *VariableHandler::getVariableData(::core::EntityID variable, bool throws)
        {
            if (manager.contains(variable))
                return manager.getEntity(variable).guiModel<models::gui::declarable::Variable>();
            if (throws)
                throw std::runtime_error("Given entity is not a variable");
            return nullptr;
        }

        void VariableHandler::onTypeSet(::core::EntityID variable, ::core::EntityID type)
        {
            if (manager.contains(type) || (type >= 1 && type <= 5))
            {
                models::gui::declarable::Variable *var = getVariableData(variable);

                if (var != nullptr)
                {
                    commands::CoreCommand::Success();
                    qDebug() << "Type set to " << type;
                    var->setVarType(type);
                }
            }
        }

        void VariableHandler::onSetTypeError(::core::EntityID variable, ::core::EntityID type, const QString &message)
        {
            if (manager.contains(type))
            {
                if (getVariableData(variable) != nullptr)
                {
                    commands::CoreCommand::Error();
                    Editor::instance().notifyError(message.toUtf8(), [](){});
                }
            }
        }

        void VariableHandler::onValueSet(::core::EntityID variable, const QString &value)
        {
            models::gui::declarable::Variable *var = getVariableData(variable);

            qDebug() << "====> On value set";
            if (var != nullptr)
            {
                commands::CoreCommand::Success();

                qDebug() << "Setting variable value";
                var->setValue(value);
//                QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());

//                if (!doc.isNull() && doc.isObject())
//                {
//                    var->setValue(doc.object());
//                }
            }
        }

        void VariableHandler::onSetValueError(::core::EntityID variable, const QString &value, const QString &message)
        {
            Q_UNUSED(value)
            Q_UNUSED(message)
            if (getVariableData(variable) != nullptr)
            {
                commands::CoreCommand::Error();
                Editor::instance().notifyError(message.toUtf8(), [](){});
            }
        }
    }
}
