#include <functional>

#include "dnai/core/instructionhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        InstructionHandler::InstructionHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void InstructionHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));

            ::core::function::instruction::onRemoved(std::bind(&InstructionHandler::onRemoved, this, _1, _2));
            ::core::function::instruction::onRemoveError(std::bind(&InstructionHandler::onRemoveError, this, _1, _2, _3));

            ::core::function::instruction::onEntryPointSet(std::bind(&InstructionHandler::onEntryPointSet, this, _1, _2));
            ::core::function::instruction::onSetEntryPointError(std::bind(&InstructionHandler::onSetEntryPointError, this, _1, _2, _3));

            ::core::function::instruction::onDataLinked(std::bind(&InstructionHandler::onDataLinked, this, _1, _2, _3, _4, _5));
            ::core::function::instruction::onLinkDataError(std::bind(&InstructionHandler::onLinkDataError, this, _1, _2, _3, _4, _5, _6));

            ::core::function::instruction::onDataUnlinked(std::bind(&InstructionHandler::onDataUnlinked, this, _1, _2, _3));
            ::core::function::instruction::onUnlinkDataError(std::bind(&InstructionHandler::onUnlinkDataError, this, _1, _2, _3, _4));

            ::core::function::instruction::onExecutionLinked(std::bind(&InstructionHandler::onExecutionLinked, this, _1, _2, _3, _4));
            ::core::function::instruction::onLinkExecutionError(std::bind(&InstructionHandler::onLinkExecutionError, this, _1, _2, _3, _4, _5));

            ::core::function::instruction::onExecutionUnlinked(std::bind(&InstructionHandler::onExecutionUnlinked, this, _1, _2, _3));
            ::core::function::instruction::onUnlinkExecutionError(std::bind(&InstructionHandler::onUnlinkExecutionError, this, _1, _2, _3, _4));
        }

        void InstructionHandler::remove(quint32 func, quint32 instruction)
        {
            Q_UNUSED(func)
            Q_UNUSED(instruction)
            /*models::Entity &function = manager.getEntity(func);

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Function.Instruction.Remove", true,
                    [&function]() {
                        ::core::function::instruction()
                    }
                )
            );*/
        }

        void InstructionHandler::setEntryPoint(quint32 function, quint32 instruction)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
        }

        void InstructionHandler::linkData(quint32 function, quint32 instruction, const QString &input, quint32 fromInstruction, const QString &output)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
            Q_UNUSED(fromInstruction)
            Q_UNUSED(output)
        }

        void InstructionHandler::unlinkData(quint32 function, quint32 instruction, const QString &input)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
        }

        void InstructionHandler::linkExecution(quint32 function, quint32 instruction, quint32 outPin, quint32 toInstruction)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outPin)
            Q_UNUSED(toInstruction)
        }

        void InstructionHandler::unlinkExecution(quint32 function, quint32 instruction, quint32 outPin)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outPin)
        }

        void InstructionHandler::onRemoved(quint32 function, quint32 instruction)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
        }

        void InstructionHandler::onRemoveError(quint32 function, quint32 instruction, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(message)
        }

        void InstructionHandler::onEntryPointSet(quint32 function, quint32 instruction)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
        }

        void InstructionHandler::onSetEntryPointError(quint32 function, quint32 instruction, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(message)
        }

        void InstructionHandler::onDataLinked(quint32 function, quint32 instruction, const QString &input, quint32 fromInstruction, const QString &output)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
            Q_UNUSED(fromInstruction)
            Q_UNUSED(output)
        }

        void InstructionHandler::onLinkDataError(quint32 function, quint32 instruction, const QString &input, quint32 fromInstruction, const QString &output, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
            Q_UNUSED(fromInstruction)
            Q_UNUSED(output)
            Q_UNUSED(message)
        }

        void InstructionHandler::onDataUnlinked(quint32 function, quint32 instruction, const QString &input)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
        }

        void InstructionHandler::onUnlinkDataError(quint32 function, quint32 instruction, const QString &input, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)
            Q_UNUSED(message)
        }

        void InstructionHandler::onExecutionLinked(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outpin)
            Q_UNUSED(toInstruction)
        }

        void InstructionHandler::onLinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outpin)
            Q_UNUSED(toInstruction)
            Q_UNUSED(message)
        }

        void InstructionHandler::onExecutionUnlinked(quint32 function, quint32 instruction, quint32 outpin)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outpin)
        }

        void InstructionHandler::onUnlinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outpin)
            Q_UNUSED(message)
        }
    }
}
