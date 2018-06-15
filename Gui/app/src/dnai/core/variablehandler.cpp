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
                if (var->varType() != ::core::UNDEFINED_ID)
                    setType(id, var->varType(), false);
                if (!var->value().isEmpty())
                    setValue(id, var->value(), false);
            }
        }

        void VariableHandler::setType(quint32 var, quint32 typ, bool save)
        {
            qDebug() << "==Core== Variable.SetType(" << var << ", " << typ << ") => save(" << save << ")";

            models::Entity &variable = manager.getEntity(var);
            models::Entity &type = manager.getEntity(typ);
            core::EntityID oldType = getVariableData(variable.id(), true)->varType();

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Variable.SetType", save,
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

        void VariableHandler::setValue(quint32 var, const QString &value, bool save)
        {
            models::Entity &variable = manager.getEntity(var);
            QString oldval = getVariableData(variable.id(), true)->value();

            qDebug() << "==Core== Variable.SetValue(" << var << ", " << value << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Variable.SetValue", save,
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
            models::gui::declarable::Variable *var = getVariableData(variable);

            commands::CoreCommand::Success();
            qDebug() << "==Core== Variable.TypeSet(" << variable << ", " << type << ")";
            var->setVarType(type);
        }

        void VariableHandler::onSetTypeError(::core::EntityID variable, ::core::EntityID type, const QString &message)
        {
            Q_UNUSED(type)
            models::Entity &var = manager.getEntity(variable);

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set type for entity " + var.name() + ": " + message);
        }

        void VariableHandler::onValueSet(::core::EntityID variable, const QString &value)
        {
            models::gui::declarable::Variable *var = getVariableData(variable);

            if (var != nullptr)
            {
                commands::CoreCommand::Success();

                qDebug() << "==Core== Variable.ValueSet(" << variable << ", " << value << ")";
                var->setValue(value);
            }
        }

        void VariableHandler::onSetValueError(::core::EntityID variable, const QString &value, const QString &message)
        {
            Q_UNUSED(value)
            Q_UNUSED(message)
            if (getVariableData(variable) != nullptr)
            {
                commands::CoreCommand::Error();
                Editor::instance().notifyError(message.toUtf8());
            }
        }
    }
}
