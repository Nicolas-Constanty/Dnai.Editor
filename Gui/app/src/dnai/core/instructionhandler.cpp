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

        void InstructionHandler::remove(quint32 func, quint32 instruction, bool save)
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

        void InstructionHandler::setEntryPoint(quint32 function, quint32 instruction, bool save)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
        }

        void InstructionHandler::linkData(quint32 function, quint32 from, const QString &output, quint32 to, const QString &input, bool save)
        {
            qDebug() << "==Core== Function.Instruction.LinkData(" << function << ", " << from << ", " << output << ", " << to << ", " << input << ") => save(" << save << ")";

            models::Entity &func = manager.getEntity(function);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.LinkData", save,
                [&func, from, output, to, input]() {
                    core::function::instruction::linkData(func.id(), from, output, to, input);
                },
                [&func, to, input]() {
                    core::function::instruction::unlinkData(func.id(), to, input);
                }
            ));
        }

        void InstructionHandler::unlinkData(quint32 function, quint32 instruction, const QString &input, bool save)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(input)

            /*qDebug() << "==Core== Function.Instruction.LinkData(" << function << ", " << instruction << ", " << input << ") => save(" << save << ")";

            models::Entity &func = manager.getEntity(function);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.UnlinkData", save,
                [&func, instruction, input]() {
                    core::function::instruction::unlinkData(func.id(), instruction, input);
                },
                nullptr; //relink data
            ));*/
        }

        void InstructionHandler::linkExecution(quint32 function, quint32 instruction, quint32 outPin, quint32 toInstruction, bool save)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outPin)
            Q_UNUSED(toInstruction)
            models::Entity &func = manager.getEntity(function);

            qDebug() << "==Core== Function.Instruction.LinkExecution(" << function << ", " << instruction << ", " << outPin << ", " << toInstruction << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.LinkExecution", save,
                [&func, instruction, outPin, toInstruction]() {
                    core::function::instruction::linkExecution(func.id(), instruction, outPin, toInstruction);
                },
                [&func, instruction, outPin]() {
                    core::function::instruction::unlinkExecution(func.id(), instruction, outPin);
                }
            ));
        }

        void InstructionHandler::unlinkExecution(quint32 function, quint32 instruction, quint32 outPin, bool save)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)
            Q_UNUSED(outPin)

            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *data = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *instr = data->getInstruction(instruction);
            models::gui::FlowLink *focusedLink = data->findFlowLink(instr->guiUuid(), outPin);

            if (focusedLink == nullptr)
            {
                qWarning() << "==Core== Function.Instruction.UnlinkExecution: The out pin " << outPin << " of the instruction " << instruction << " in function " << function << " is not linked";
                return;
            }

            qDebug() << "==Core== Function.Instruction.UnlinkExecution(" << function << ", " << instruction << ", " << outPin << ") => save(" << save << ")";

            models::gui::Instruction *toInstruction = data->getInstruction(focusedLink->data().to);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.UnlinkExecution", save,
                [&func, instr, outPin]() {
                    core::function::instruction::unlinkExecution(func.id(), instr->Uid(), outPin);
                },
                [&func, instr, outPin, toInstruction]() {
                    core::function::instruction::linkExecution(func.id(), instr->Uid(), outPin, toInstruction->Uid());
                }
            ));
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

        void InstructionHandler::onDataLinked(quint32 function, quint32 fromI, const QString &output, quint32 toI, const QString &input)
        {
            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *dat = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *from = dat->getInstruction(fromI);
            models::gui::Instruction *to = dat->getInstruction(toI);

            /* to do: implement the link in the model */
            auto iolink = new models::gui::IoLink();
            models::gui::data::IoLink data;
            data.inputName = input;
            data.outputName = output;
            data.inputUuid = from->guiUuid();
            data.outputUuid = to->guiUuid();
            iolink->setData(data);
            dat->appendIoLink(iolink);

            commands::CoreCommand::Success();

            qDebug() << "==Core== Function.Instruction.DataLinked(" << function << ", " << fromI << ", " << output << ", " << toI << ", " << input << ")";

            emit dataLinked(&func, from, output, to, input);
        }

        void InstructionHandler::onLinkDataError(quint32, quint32 from, const QString &output, quint32 to, const QString &input, const QString &message)
        {
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to link instruction_" + QString::number(from) + "[" + output + "] to instruction_" + QString::number(to) + "[" + input + "]: " + message);
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
            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *data = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *from = data->getInstruction(instruction);
            models::gui::Instruction *to = data->getInstruction(toInstruction);
            models::gui::FlowLink *link = new models::gui::FlowLink();
            models::gui::data::FlowLink flowdata;

            flowdata.from = from->guiUuid();
            flowdata.to = to->guiUuid();
            flowdata.outIndex = outpin;
            link->setData(flowdata);
            data->appendFlowLink(link);

            commands::CoreCommand::Success();

            qDebug() << "==Core== Function.Instruction.ExecutionLinked(" << function << ", " << instruction << ", " << outpin << ", " << toInstruction << ")";

            emit executionLinked(&func, from, outpin, to);
        }

        void InstructionHandler::onLinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction, const QString &message)
        {
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to link pin " + QString::number(outpin) + " of instruction " + QString::number(instruction) + " to instruction " + QString::number(toInstruction) + ": " + message);
        }

        void InstructionHandler::onExecutionUnlinked(quint32 function, quint32 instruction, quint32 outpin)
        {
            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *data = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *from = data->getInstruction(instruction);
            models::gui::FlowLink *lnk = data->findFlowLink(from->guiUuid(), outpin);

            if (lnk != nullptr)
            {
                qDebug() << "==Core== Function.Instruction.ExecutionUnlinked(" << function << ", " << instruction << ", " << outpin << ")";
                data->removeFlowLink(lnk);
                emit executionUnlinked(&func, from, outpin);
            }
            else
            {
                qWarning() << "==Core== Function.Instruction.ExecutionUnlinked: Pin " << outpin << " of instruction " << instruction << "in function " << function << " is not linked";
            }
        }

        void InstructionHandler::onUnlinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, const QString &message)
        {
            commands::CoreCommand::Success();
            Editor::instance().notifyError("Unable to unlink pin " + QString::number(outpin) + " of instruction " + QString::number(instruction) + " in function " + QString::number(function) + ": " + message);
        }
    }
}
