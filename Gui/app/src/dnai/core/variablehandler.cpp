#include <functional>

#include <QJsonDocument>
#include <QJsonObject>

#include "core.h"

#include "dnai/core/variablehandler.h"
#include "dnai/commands/corecommand.h"
#include "dnai/models/gui/declarable/variable.h"

#include "dnai/commands/commandmanager.h"

#include "dnai/commands/corecommand.h"

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
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));

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

                /*if (var->varType() != enums::core::UNDEFINED_ID)
                    setType(manager.getEntity(id), manager.getEntity(var->varType()));
                if (!var->value().empty())
                    setValue(manager.getEntity(id), var->value());*/
            }
        }

        void VariableHandler::setType(models::Entity const &variable, models::Entity const &type)
        {
            ::core::EntityID oldType = getVariableData(variable.id(), true)->varType();

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

        void VariableHandler::setValue(models::Entity const &variable, const QString &value)
        {
            QString val = value;
            QString oldval = getVariableData(variable.id(), true)->value();

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Variable.SetValue", true,
                    /*
                     * Execute
                     */
                    [&variable, val]() {
                      ::core::variable::setValue(variable.id(), val);
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
            if (manager.contains(type))
            {
                models::gui::declarable::Variable *var = getVariableData(variable);

                if (var != nullptr)
                {
                    commands::CoreCommand::Success();

                    var->setVarType(type);
                }
            }
        }

        void VariableHandler::onSetTypeError(::core::EntityID variable, ::core::EntityID type, const QString &message)
        {
            Q_UNUSED(message)
            if (manager.contains(type))
            {
                if (getVariableData(variable) != nullptr)
                    commands::CoreCommand::Error();
            }
        }

        void VariableHandler::onValueSet(::core::EntityID variable, const QString &value)
        {
            models::gui::declarable::Variable *var = getVariableData(variable);

            if (var != nullptr)
            {
                commands::CoreCommand::Success();

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
            }
        }
    }
}