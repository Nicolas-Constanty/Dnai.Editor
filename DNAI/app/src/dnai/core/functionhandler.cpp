#include <functional>

#include "dnai/core/functionhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        FunctionHandler::FunctionHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void FunctionHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));

            ::core::function::onParameterSet(std::bind(&FunctionHandler::onParameterSet, this, _1, _2));
            ::core::function::onSetParameterError(std::bind(&FunctionHandler::onSetParameterError, this, _1, _2, _3));
            ::core::function::onReturnSet(std::bind(&FunctionHandler::onReturnSet, this, _1, _2));
            ::core::function::onSetReturnError(std::bind(&FunctionHandler::onSetReturnError, this, _1, _2, _3));
        }

        void FunctionHandler::onEntityAdded(::core::EntityID id, models::Entity &added)
        {
            Q_UNUSED(id)
            Q_UNUSED(added)
        }

        void FunctionHandler::setParameter(const models::Entity &function, const models::Entity &paramVar)
        {
            if (getFunctionData(function.id()) != nullptr && paramVar.parentItem() == &function)
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetParameter", true,
                        std::bind(&::core::function::setParameter, function.id(), paramVar.name()),
                        nullptr /* not implemented yet */
                    )
                );
        }

        void FunctionHandler::setReturn(const models::Entity &function, const models::Entity &returnVar)
        {
            if (getFunctionData(function.id()) != nullptr && returnVar.parentItem() == &function)
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetReturn", true,
                        std::bind(&::core::function::setReturn, function.id(), returnVar.name()),
                        nullptr /* not implemented yet */
                    )
                );
        }

        models::gui::declarable::Function *FunctionHandler::getFunctionData(::core::EntityID function, bool throws)
        {
            if (manager.contains(function))
            {
                models::gui::declarable::Function *func = manager.getEntity(function).guiModel<models::gui::declarable::Function>();

                if (func != nullptr)
                    return func;
            }

            if (throws)
                throw std::runtime_error("Given entity is not a function");

            return nullptr;
        }

        void FunctionHandler::onParameterSet(::core::EntityID function, const QString &paramName)
        {
            Q_UNUSED(function)
            Q_UNUSED(paramName)
        }

        void FunctionHandler::onSetParameterError(::core::EntityID function, const QString &paramName, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(paramName)
            Q_UNUSED(message)
        }

        void FunctionHandler::onReturnSet(::core::EntityID function, const QString &returnName)
        {
            Q_UNUSED(function)
            Q_UNUSED(returnName)
        }

        void FunctionHandler::onSetReturnError(::core::EntityID function, const QString &returnName, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(returnName)
            Q_UNUSED(message)
        }


    }
}
