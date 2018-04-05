#include <functional>

#include <QJsonDocument>
#include <QJsonObject>

#include "core.h"

#include "dnai/core/variablehandler.h"
#include "dnai/commands/corecommand.h"
#include "dnai/models/gui/declarable/variable.h"

#include "dnai/commands/commandmanager.h"

#include "dnai/commands/core/variable/settypecommand.h"
#include "dnai/commands/core/variable/setvaluecommand.h"

using namespace std::placeholders;

namespace dnai
{
    namespace core
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

        void VariableHandler::onEntityAdded(enums::core::EntityID id, models::Entity &entity)
        {
            models::gui::declarable::Variable *var = getVariableData(id);

            if (var != nullptr)
            {
                if (var->varType() != enums::core::UNDEFINED_ID)
                    setType(manager.getEntity(id), manager.getEntity(var->varType()));
                if (!var->value().empty())
                    setValue(manager.getEntity(id), var->value());
            }
        }

        void VariableHandler::setType(models::Entity const &variable, models::Entity const &type)
        {
            commands::CommandManager::Instance()->exec(new commands::variable::SetTypeCommand(variable, type));
        }

        void VariableHandler::setValue(models::Entity const &variable, const QJsonObject &value)
        {
            QJsonDocument doc(value);

            commands::CommandManager::Instance()->exec(new commands::variable::SetValueCommand(variable, doc.toJson(QJsonDocument::Compact)));
        }

        models::gui::declarable::Variable   *VariableHandler::getVariableData(enums::core::EntityID variable)
        {
            if (manager.contains(variable))
                return manager.getEntity(variable).guiModel<models::gui::declarable::Variable>();
            return nullptr;
        }

        void VariableHandler::onTypeSet(enums::core::EntityID variable, enums::core::EntityID type)
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

        void VariableHandler::onSetTypeError(enums::core::EntityID variable, enums::core::EntityID type, const QString &message)
        {
            if (manager.contains(type))
            {
                if (getVariableData(variable) != nullptr)
                    commands::CoreCommand::Error();
            }
        }

        void VariableHandler::onValueSet(enums::core::EntityID variable, const QString &value)
        {
            models::gui::declarable::Variable *var = getVariableData(variable);

            if (var != nullptr)
            {
                commands::CoreCommand::Success();

                QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());

                if (!doc.isNull() && doc.isObject())
                {
                    var->setValue(doc.object());
                }
            }
        }

        void VariableHandler::onSetValueError(enums::core::EntityID variable, const QString &value, const QString &message)
        {
            if (getVariableData(variable) != nullptr)
            {
                commands::CoreCommand::Error();
            }
        }
    }
}
