#include <functional>
#include <algorithm>
#include <unordered_set>

#include "dnai/core/functionhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"
#include "dnai/models/instruction.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        FunctionHandler::FunctionHandler(EntityManager &manager) :
            manager(manager),
            m_instruction(manager)
        {

        }

        void FunctionHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));
            QObject::connect(&manager,  SIGNAL(entityRemoved(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityRemoved(::core::EntityID,models::Entity&)));

            ::core::function::onParameterSet(std::bind(&FunctionHandler::onParameterSet, this, _1, _2));
            ::core::function::onSetParameterError(std::bind(&FunctionHandler::onSetParameterError, this, _1, _2, _3));
            ::core::function::onReturnSet(std::bind(&FunctionHandler::onReturnSet, this, _1, _2));
            ::core::function::onSetReturnError(std::bind(&FunctionHandler::onSetReturnError, this, _1, _2, _3));
            ::core::function::onInstructionAdded(std::bind(&FunctionHandler::onInstructionAdded, this, _1, _2, _3, _4));
            ::core::function::onAddInstructionError(std::bind(&FunctionHandler::onAddInstructionError, this, _1, _2, _3, _4));

            m_instruction.setup();
        }

        void FunctionHandler::onEntityAdded(::core::EntityID id, models::Entity &added)
        {
            Q_UNUSED(id)
            Q_UNUSED(added)

            if (!pendingParams.empty()
                && added.containerId() == pendingParams.front().first
                && added.name() == pendingParams.front().second)
            {
                params.push(&added);
                setParameter(added.containerId(), added.name());
                pendingParams.pop();
            }
            else if (!pendingRet.empty()
                && added.containerId() == pendingRet.front().first
                && added.name() == pendingRet.front().second)
            {
                returns.push(&added);
                setReturn(added.containerId(), added.name());
                pendingRet.pop();
            }
            else
            {
                models::gui::declarable::Function *func = getFunctionData(id);

                if (func != nullptr)
                {
                    for (models::Entity *child : added.childrenItem())
                    {
                        if (std::find_if(func->inputs().begin(), func->inputs().end(), [child](models::Entity *curr){ return curr->name() == child->name(); }) != func->inputs().end())
                        {
                            pendingParameter(id, child->name());
                        }
                        else if (std::find_if(func->outputs().begin(), func->outputs().end(), [child](models::Entity *curr){ return curr->name() == child->name(); }) != func->outputs().end())
                        {
                            pendingReturn(id, child->name());
                        }
                    }
                    func->setInputs(QList<models::Entity*>());
                    func->setOutputs(QList<models::Entity*>());

                    pendingFunctionInstructions.push_back(&added);
                }
            }

            refreshPendingFunctionInstructions();
        }

        void FunctionHandler::onEntityRemoved(EntityID id, models::Entity &removed)
        {
            if (!pendingRmParam.empty()
                && pendingRmParam.front().first == removed.containerId()
                && pendingRmParam.front().second == removed.name())
            {
                models::Entity &func = manager.getEntity(removed.containerId());

                func.guiModel<models::gui::declarable::Function>()->removeInput(removed.name());
                pendingRmParam.pop();
            }
            else if (!pendingRmRet.empty()
                     && pendingRmRet.front().first == removed.containerId()
                     && pendingRmRet.front().second == removed.name())
            {
                models::Entity &func = manager.getEntity(removed.containerId());

                func.guiModel<models::gui::declarable::Function>()->removeOutput(removed.name());
                pendingRmRet.pop();
            }
        }

        void FunctionHandler::pendingParameter(quint32 func, const QString &paramName)
        {
            pendingParams.push(std::make_pair(func, paramName));
        }

        void FunctionHandler::pendindRemoveParam(quint32 func, const QString &paramName)
        {
            pendingRmParam.push(std::make_pair(func, paramName));
        }

        void FunctionHandler::pendingReturn(quint32 func, const QString &returnName)
        {
            pendingRet.push(std::make_pair(func, returnName));
        }

        void FunctionHandler::pendingRmReturn(quint32 func, const QString &returnName)
        {
            pendingRmRet.push(std::make_pair(func, returnName));
        }

        void FunctionHandler::setParameter(quint32 func, QString const &paramName)
        {
            models::Entity &function = manager.getEntity(func);

            qDebug() << "Set as parameter";

            if (getFunctionData(function.id()) != nullptr)
            {
                qDebug() << "Really set as parameter";
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetParameter", true,
                        std::bind(&::core::function::setParameter, function.id(), paramName),
                        nullptr /* not implemented yet */
                    )
                );
            }
        }

        void FunctionHandler::setReturn(quint32 func, QString const &retName)
        {
            models::Entity &function = manager.getEntity(func);

            if (getFunctionData(function.id()) != nullptr)
                commands::CommandManager::Instance()->exec(
                    new commands::CoreCommand("Function.SetReturn", true,
                        std::bind(&::core::function::setReturn, function.id(), retName),
                        nullptr /* not implemented yet */
                    )
                            );
        }

        void FunctionHandler::addInstruction(quint32 func, quint32 instrType, const QList<quint32> &arguments)
        {
            models::Entity &function = manager.getEntity(func);

            qDebug() << "Add instruction(" << func << ", " << instrType << ", " << arguments << ")";
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

        /**
         * @brief FunctionHandler::refreshPendingFunctionInstructions
         *
         * This function tries to declared function instructions for thoses who needed entity that wasn't created yet
         *
         * Ex:
         *     - A function has a list of instructions
         *     - A getter is an instruction that need the id of a variable
         *     - If the variable is not created yet, we can't declare the getter
         *     - Then we need to wait until the variable is created
         *     - So we push the function in a list
         *     - Each time an entity is added, we try to redeclare the instructions
         *     - If the redeclaration went fine, we erase the function from the list
         *     - Either, we left the function in place
         */
        void FunctionHandler::refreshPendingFunctionInstructions()
        {
            //we visit all the functions from the list
            for (std::list<models::Entity *>::iterator it = pendingFunctionInstructions.begin(); it != pendingFunctionInstructions.end();)
            {
                //we get the function model
                models::Function *func = getFunctionData((*it)->id());

                //this queue is the instructions of the function
                std::queue<models::gui::Instruction *> instructions;
                //this queue is the list of entities to send
                std::queue<QList<quint32>> linked;

                //this is to check that we can declare all the instructions
                bool isfull = true;

                //we visit all the instructions of the function
                for (models::gui::Instruction *curr : func->instructions())
                {
                    //this is the list of entities to send
                    QList<quint32> construction;
                    //this is to check that all the entities exist
                    bool add = true;

                    //we visit all the entities to send for the instruction
                    for (QString const &cname : curr->linked())
                    {
                        models::Entity *associated = manager.findByFullname(cname);

                        //if the entity doesn't exists, we break the loop
                        if (associated == nullptr)
                        {
                            add = false;
                            break;
                        }
                        construction.append(associated->id());
                    }

                    //if the construction list is ok
                    if (add)
                    {
                        //we add it to the queue
                        instructions.push(curr);
                        linked.push(construction);
                    }
                    else
                    {
                        //in case of an error, we break the loop
                        isfull = false;
                        break;
                    }
                }

                //if we can declare all the instructions
                if (isfull)
                {
                    //declare everything
                    while (!instructions.empty())
                    {
                        pendingInstruction.push(instructions.front());
                        addInstruction((*it)->id(), instructions.front()->instruction_id(), linked.front());
                        instructions.pop();
                        linked.pop();
                    }
                    //and remove the function from the list
                    it = pendingFunctionInstructions.erase(it);
                }
                else
                {
                    //or just increment to the next function
                    ++it;
                }
            }
        }

        void FunctionHandler::onParameterSet(::core::EntityID func, const QString &paramName)
        {
            Q_UNUSED(func)
            Q_UNUSED(paramName)

            models::Entity &function = manager.getEntity(func);

            if (params.empty())
                return;

            models::Entity *param = params.front();

            models::gui::declarable::Function *gui = function.guiModel<models::gui::declarable::Function>();

            if (gui != nullptr && param->name() == paramName)
            {
                qDebug() << "Variable " << param->name() << "(" << param->id() << ") set as parameter";
                if (!gui->inputs().contains(param))
                    gui->addInput(param);
                if (!function.childrenItem().contains(param))
                    function.appendChild(param);
                commands::CoreCommand::Success();
                params.pop();
            }
        }

        void FunctionHandler::onSetParameterError(::core::EntityID function, const QString &paramName, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(paramName)
            Q_UNUSED(message)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set variable " + paramName + " as parameter: " + message);
        }

        void FunctionHandler::onReturnSet(::core::EntityID function, const QString &returnName)
        {
            Q_UNUSED(function)
            Q_UNUSED(returnName)

            models::Entity &func = manager.getEntity(function);

            if (returns.empty())
                return;

            models::Entity *var = returns.front();

            models::gui::declarable::Function *gui = func.guiModel<models::gui::declarable::Function>();

            if (gui != nullptr && var->name() == returnName)
            {
                if (!gui->outputs().contains(var))
                    gui->addOutput(var);
                if (!func.childrenItem().contains(var))
                    func.appendChild(var);
                returns.pop();
                commands::CoreCommand::Success();
            }
        }

        void FunctionHandler::onSetReturnError(::core::EntityID function, const QString &returnName, const QString &message)
        {
            Q_UNUSED(function)
            Q_UNUSED(returnName)
            Q_UNUSED(message)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to set return: " + message);
        }

        void FunctionHandler::onInstructionAdded(EntityID function, INSTRUCTION type, const std::list<EntityID> &arguments, InstructionID instruction)
        {
            commands::CoreCommand::Success();

            Q_UNUSED(function)
            Q_UNUSED(type)
            Q_UNUSED(arguments)
            Q_UNUSED(instruction)

            models::gui::declarable::Function *func = getFunctionData(function);

            qDebug() << "Instruction added";
            if (func != nullptr)
            {
                qDebug() << "===== Created ok =====";
                models::gui::Instruction *instr;

                if (pendingInstruction.empty())
                {
                    instr = new models::gui::Instruction();
                    instr->setInstructionId(type);
                    instr->setUid(instruction);

                    QList<QString> linked;

                    for (quint32 curr : arguments) {
                        linked.append(manager.getEntity(curr).fullName());
                    }

                    instr->setLinkedEntities(linked);
                    func->addInstruction(instr);
                }
                else
                {
                    instr = pendingInstruction.front();
                    pendingInstruction.pop();
                }
                emit instructionAdded(&manager.getEntity(function), instr);
            }

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
            Editor::instance().notifyError("Unable to create instruction: " + messsage);
            emit addInstructionError(function, type, QList<quint32>::fromStdList(arguments), messsage);
        }

        InstructionHandler *FunctionHandler::instruction()
        {
            return &m_instruction;
        }
    }
}
