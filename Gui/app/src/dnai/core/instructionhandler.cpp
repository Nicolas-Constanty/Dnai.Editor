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
            ::core::function::instruction::onDataLinked(std::bind(&InstructionHandler::onDataLinked, this, _1, _2, _3, _4, _5));
            ::core::function::instruction::onLinkDataError(std::bind(&InstructionHandler::onLinkDataError, this, _1, _2, _3, _4, _5, _6));

            ::core::function::instruction::onDataUnlinked(std::bind(&InstructionHandler::onDataUnlinked, this, _1, _2, _3));
            ::core::function::instruction::onUnlinkDataError(std::bind(&InstructionHandler::onUnlinkDataError, this, _1, _2, _3, _4));

            ::core::function::instruction::onExecutionLinked(std::bind(&InstructionHandler::onExecutionLinked, this, _1, _2, _3, _4));
            ::core::function::instruction::onLinkExecutionError(std::bind(&InstructionHandler::onLinkExecutionError, this, _1, _2, _3, _4, _5));

            ::core::function::instruction::onExecutionUnlinked(std::bind(&InstructionHandler::onExecutionUnlinked, this, _1, _2, _3));
            ::core::function::instruction::onUnlinkExecutionError(std::bind(&InstructionHandler::onUnlinkExecutionError, this, _1, _2, _3, _4));

            ::core::function::instruction::onInputValueSet(std::bind(&InstructionHandler::onInputValueSet, this, _1, _2, _3, _4));
            ::core::function::instruction::onSetInputValueError(std::bind(&InstructionHandler::onSetInputValueError, this, _1, _2, _3, _4, _5));
        }

        void InstructionHandler::linkData(quint32 function, quint32 from, const QString &output, quint32 to, const QString &input, bool save)
        {
            qDebug() << "==Core== Function.Instruction.LinkData(" << function << ", " << from << ", " << output << ", " << to << ", " << input << ") => save(" << save << ")";

            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *fromI = data->getInstruction(from);
            models::gui::Instruction *toI = data->getInstruction(to);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.LinkData", save,
                [&func, fromI, output, toI, input]() {
                    core::function::instruction::linkData(func.id(), fromI->Uid(), output, toI->Uid(), input);
                },
                [&func, toI, input]() {
                    core::function::instruction::unlinkData(func.id(), toI->Uid(), input);
                }
            ));
        }

        void InstructionHandler::unlinkData(quint32 function, quint32 instruction, const QString &input, bool save)
        {
            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *to = data->getInstruction(instruction);
            models::gui::IoLink *focusedLink = data->findIOLink(to->guiUuid(), input);

            if (focusedLink == nullptr)
            {
                qWarning() << "==Core== Function.Instruction.UnLinkData: Input " << input << " of instruction " << instruction << " in function " << function << " is not linked";
                return;
            }

            qDebug() << "==Core== Function.Instruction.UnLinkData(" << function << ", " << instruction << ", " << input << ") => save(" << save << ")";

            models::gui::Instruction *from = data->getInstruction(focusedLink->data().outputUuid);
            QString output = focusedLink->data().outputName;

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.UnlinkData", save,
                [&func, to, input]() {
                    core::function::instruction::unlinkData(func.id(), to->Uid(), input);
                },
                [&func, from, output, to, input]() {
                    core::function::instruction::linkData(func.id(), from->Uid(), output, to->Uid(), input);
                }
            ));
        }

        void InstructionHandler::linkExecution(quint32 function, quint32 instruction, quint32 outPin, quint32 toInstruction, bool save)
        {
            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *from = data->getInstruction(instruction);
            models::gui::Instruction *to = data->getInstruction(toInstruction);

            qDebug() << "==Core== Function.Instruction.LinkExecution(" << function << ", " << instruction << ", " << outPin << ", " << toInstruction << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.LinkExecution", save,
                [&func, from, outPin, to]() {
                    core::function::instruction::linkExecution(func.id(), from->Uid(), outPin, to->Uid());
                },
                [&func, from, outPin]() {
                    core::function::instruction::unlinkExecution(func.id(), from->Uid(), outPin);
                }
            ));
        }

        void InstructionHandler::unlinkExecution(quint32 function, quint32 instruction, quint32 outPin, bool save)
        {
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

        void InstructionHandler::setInputValue(quint32 function, quint32 instruction, const QString &input, const QString &value, bool save)
        {
            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *instr = data->getInstruction(instruction);

            QString oldValue = "";

            qDebug() << "==Core== Function.Instruction.SetInputValue(" << function << ", " << instruction << ", " << input << ", " << value << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Function.Instruction.SetInputValue", save,
                [&func, instr, input, value]() {
                    core::function::instruction::setInputValue(func.id(), instr->Uid(), input, value);
                },
                [&func, instr, input, oldValue]() {
                    if (!oldValue.isEmpty())
                        core::function::instruction::setInputValue(func.id(), instr->Uid(), input, oldValue);
                }
            ));
        }

        void InstructionHandler::onDataLinked(quint32 function, quint32 fromI, const QString &output, quint32 toI, const QString &input)
        {
            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *dat = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *from = dat->getInstruction(fromI);
            models::gui::Instruction *to = dat->getInstruction(toI);

            if (!dat->findIOLink(to->guiUuid(), input))
                dat->appendIoLink(createIoLink(from->guiUuid(), output, to->guiUuid(), input));

            commands::CoreCommand::Success();

            qDebug() << "==Core== Function.Instruction.DataLinked(" << function << ", " << fromI << ", " << output << ", " << toI << ", " << input << ")";

            emit dataLinked(&func, from, output, to, input);
        }

        void InstructionHandler::onLinkDataError(quint32, quint32 from, const QString &output, quint32 to, const QString &input, const QString &message)
        {
            commands::CoreCommand::Error();
            qWarning() << "==Core== Instruction.LinkDataError: " << "Unable to link instruction_" + QString::number(from) + "[" + output + "] to instruction_" + QString::number(to) + "[" + input + "]: " + message;
            //Editor::instance().notifyError("Unable to link instruction_" + QString::number(from) + "[" + output + "] to instruction_" + QString::number(to) + "[" + input + "]: " + message);
        }

        void InstructionHandler::onDataUnlinked(quint32 function, quint32 instruction, const QString &input)
        {
            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *instr = data->getInstruction(instruction);
            models::gui::IoLink *link = data->findIOLink(instr->guiUuid(), input);

            if (link != nullptr)
            {
                qWarning() << "==Core== Function.Instruction.DataUnlinked(" << function << ", " << instruction << ", " << input << ")";
                commands::CoreCommand::Success();
                data->removeIoLink(link);
                emit dataUnlinked(&func, instr, input);
            }
            else
            {
                qWarning() << "==Core== Function.Instruction.DataUnlinked: Input " << input << " of instruction " << instruction << " in function " << function << " is not linked";
            }
        }

        void InstructionHandler::onUnlinkDataError(quint32 function, quint32 instruction, const QString &input, const QString &message)
        {
            commands::CoreCommand::Error();
            qWarning() << "==Core== Instruction.UnlinkDataError: " << "Unable to unlink input " + input + " of instruction " + QString::number(instruction) + " in function " + QString::number(function) + ": " + message;
            //Editor::instance().notifyError("Unable to unlink input " + input + " of instruction " + QString::number(instruction) + " in function " + QString::number(function) + ": " + message);
        }

        void InstructionHandler::onExecutionLinked(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction)
        {
            models::Entity &func = manager.getEntity(function);
            models::gui::declarable::Function *data = func.guiModel<models::gui::declarable::Function>();
            models::gui::Instruction *from = data->getInstruction(instruction);
            models::gui::Instruction *to = data->getInstruction(toInstruction);

            if (!data->findFlowLink(from->guiUuid(), outpin, to->guiUuid()))
                data->appendFlowLink(createFlowLink(from->guiUuid(), outpin, to->guiUuid()));

            commands::CoreCommand::Success();

            qDebug() << "==Core== Function.Instruction.ExecutionLinked(" << function << ", " << instruction << ", " << outpin << ", " << toInstruction << ")";

            emit executionLinked(&func, from, outpin, to);
        }

        void InstructionHandler::onLinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction, const QString &message)
        {
            Q_UNUSED(function)
            commands::CoreCommand::Error();
            qWarning() << "==Core== Function.Instruction.LinkExecutionError(" << function << ", " << instruction << ", " << outpin << ", " << toInstruction << ", " << message << ")";
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
                commands::CoreCommand::Success();
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
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to unlink pin " + QString::number(outpin) + " of instruction " + QString::number(instruction) + " in function " + QString::number(function) + ": " + message);
        }

        void InstructionHandler::onInputValueSet(quint32 function, quint32 instruction, const QString &input, const QString &value)
        {
            models::Entity &func = manager.getEntity(function);
            models::Function *data = func.guiModel<models::Function>();
            models::gui::Instruction *instr = data->getInstruction(instruction);
            models::gui::Input *inp = instr->getInput(input);

            inp->setValue(value);

            qDebug() << "==Core== Function.Instruction.InputValueSet(" << function << ", " << instruction << ", " << input << ", " << value << ")";
            commands::CoreCommand::Success();
            emit inputValueSet(&func, instr, input, value);
        }

        void InstructionHandler::onSetInputValueError(quint32 function, quint32 instruction, const QString &input, const QString &value, const QString &msg)
        {
            Q_UNUSED(function)
            Q_UNUSED(instruction)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to value " + value + " to input " + input + ": " + msg);
        }

        void InstructionHandler::onInstructionAdded(models::Entity *func, models::gui::Instruction *instruction)
        {
            models::Function *data = func->guiModel<models::Function>();

            m_instructions[instruction->guiUuid()] = instruction;

            for (models::gui::FlowLink *curr : data->flowlinks())
            {
                if (curr->data().to == instruction->guiUuid()
                    || curr->data().from == instruction->guiUuid())
                {
                    flowlink_to_replicate[curr] = func;
                }
            }

            refreshLinks();
        }

        void InstructionHandler::onInstructionRemoved(models::Entity *func, models::gui::Instruction *instruction)
        {
            Q_UNUSED(func)

            m_instructions.remove(instruction->guiUuid());
        }

        models::gui::IoLink *InstructionHandler::createIoLink(const QUuid &from, const QString &output, const QUuid &to, const QString &input)
        {
            models::gui::IoLink *iolink = new models::gui::IoLink();
            models::gui::data::IoLink data;

            data.outputUuid = from;
            data.outputName = output;

            data.inputUuid = to;
            data.inputName = input;

            iolink->setData(data);
            return iolink;
        }

        models::gui::FlowLink *InstructionHandler::createFlowLink(const QUuid &from, int outindex, const QUuid &to)
        {
            models::gui::FlowLink *link = new models::gui::FlowLink();
            models::gui::data::FlowLink flowdata;

            flowdata.from = from;
            flowdata.to = to;
            flowdata.outIndex = outindex;
            link->setData(flowdata);
            return link;
        }

        void InstructionHandler::refreshLinks()
        {
            for (std::unordered_map<models::gui::IoLink *, models::Entity *>::iterator it = iolink_to_replicate.begin(); it != iolink_to_replicate.end();)
            {
                models::gui::IoLink *curr = it->first;
                models::Entity *func = it->second;
                models::gui::Instruction *from = getInstruction(curr->data().outputUuid);
                models::gui::Instruction *to = getInstruction(curr->data().inputUuid);

                if (from != nullptr && from->hasOutput(curr->data().outputName)
                    && to != nullptr && to->hasInput(curr->data().inputName))
                {
                    linkData(func->id(), from->Uid(), curr->data().outputName, to->Uid(), curr->data().inputName, false);
                    it = iolink_to_replicate.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            for (std::unordered_map<models::gui::FlowLink *, models::Entity *>::iterator it = flowlink_to_replicate.begin(); it != flowlink_to_replicate.end();)
            {
                models::gui::FlowLink *curr = it->first;
                models::Entity *func = it->second;
                models::gui::Instruction *from = getInstruction(curr->data().from);
                models::gui::Instruction *to = getInstruction(curr->data().to);

                if (from != nullptr && to != nullptr)
                {
                    linkExecution(func->id(), from->Uid(), curr->data().outIndex, to->Uid(), false);
                    it = flowlink_to_replicate.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        bool InstructionHandler::contains(const QUuid &instGuid) const
        {
            return m_instructions.contains(instGuid);
        }

        models::gui::Instruction *InstructionHandler::getInstruction(const QUuid &guid) const
        {
            return m_instructions[guid];
        }

        QList<models::gui::Instruction *> InstructionHandler::getInstructionsOfPath(const QString &nodeMenupath) const
        {
            QList<models::gui::Instruction *> lst;

            for (models::gui::Instruction *curr : m_instructions)
            {
                if (curr->nodeMenuPath() == nodeMenupath)
                    lst.append(curr);
            }
            return lst;
        }
    }
}
