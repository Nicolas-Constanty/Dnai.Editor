#include <functional>

#include "dnai/core/functionhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

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

            /*foreach (instruction in entity.instructions)
            {
                addInstruction(entity, instruction.id, instruction.construction);
            }

            foreach (instruction in entity.instructions)
            {
                //link data: function [ok], instruction [ok], input [ok], output [ok],
                //link flow
            }*/
        }

        void FunctionHandler::setParameter(quint32 func, quint32 param)
        {
            models::Entity &function = manager.getEntity(func);
            models::Entity &paramVar = manager.getEntity(param);

            if (getFunctionData(function.id()) != nullptr && paramVar.parentItem() == &function)
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetParameter", true,
                        std::bind(&::core::function::setParameter, function.id(), paramVar.name()),
                        nullptr /* not implemented yet */
                    )
                );
        }

        void FunctionHandler::setReturn(quint32 func, quint32 ret)
        {
            models::Entity &function = manager.getEntity(func);
            models::Entity &returnVar = manager.getEntity(ret);

            if (getFunctionData(function.id()) != nullptr && returnVar.parentItem() == &function)
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetReturn", true,
                        std::bind(&::core::function::setReturn, function.id(), returnVar.name()),
                        nullptr /* not implemented yet */
                    )
                            );
        }

        void FunctionHandler::addInstruction(quint32 func, quint32 instrType, const QList<core::EntityID> &arguments)
        {
            models::Entity &function = manager.getEntity(func);

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Function.AddInstruction", true,
                    [&function, instrType, arguments](){
                        ::core::function::addInstruction(function.id(), static_cast<core::INSTRUCTION>(instrType), arguments.toStdList());
                    },
                    nullptr // find a system to get the freshly created instruction id in order to remove it
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

        void FunctionHandler::onInstructionAdded(EntityID function, INSTRUCTION type, const std::list<EntityID> &arguments, InstructionID instruction)
        {
            commands::CoreCommand::Success();

            Q_UNUSED(function)
            Q_UNUSED(type)
            Q_UNUSED(arguments)
            Q_UNUSED(instruction)
            /*
             * Find the models::Entity
             * Find the models::gui::declarable::function
             * Create the correct instruction
             * Add the instruction to function
             */
        }

        void FunctionHandler::onAddInstructionError(EntityID function, INSTRUCTION type, const std::list<EntityID> &arguments, const QString &messsage)
        {
            Q_UNUSED(function)
            Q_UNUSED(type)
            Q_UNUSED(arguments)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to create instruction: " + messsage, [](){});
        }
    }
}
