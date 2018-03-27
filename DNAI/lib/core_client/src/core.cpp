#include "Cerealizable/List.hpp"

#include "core.h"

#include "client.h"

namespace core
{
    void connect(qint16 serverPort)
    {
        Client::serverPort = serverPort;
        Client::shared();
    }

    namespace declarator
    {
        void declare(EntityID declarator, ENTITY type, const QString &name, VISIBILITY visibility)
        {
            Client::shared().callCommand("DECLARATOR.DECLARE", declarator, type, name, visibility);
        }

        void onDeclared(const std::function<void (EntityID, ENTITY, QString, VISIBILITY, EntityID)> &then)
        {
            Client::shared().registerReply("DECLARATOR.DECLARED", then);
        }

        void onDeclareError(const std::function<void (EntityID, ENTITY, QString, VISIBILITY, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.DECLARE.ERROR", error);
        }

        void remove(EntityID declarator, const QString &name)
        {
            Client::shared().callCommand("DECLARATOR.REMOVE", declarator, name);
        }

        void onRemoved(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("DECLARATOR.REMOVED", then);
        }

        void onRemoveError(const std::function<void (EntityID, QString, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.REMOVE.ERROR", error);
        }

        void rename(EntityID declarator, const QString &name, const QString &newName)
        {
            Client::shared().callCommand("DECLARATOR.RENAME", declarator, name, newName);
        }

        void onRenamed(const std::function<void (EntityID, QString, QString)> &then)
        {
            Client::shared().registerReply("DECLARATOR.RENAMED", then);
        }

        void onRenameError(const std::function<void (EntityID, QString, QString, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.RENAME.ERROR", error);
        }

        void move(EntityID declarator, const QString &name, EntityID newParent)
        {
            Client::shared().callCommand("DECLARATOR.MOVE", declarator, name, newParent);
        }

        void onMoved(const std::function<void (EntityID, QString, EntityID)> &then)
        {
            Client::shared().registerReply("DECLARATOR.MOVED", then);
        }

        void onMoveError(const std::function<void (EntityID, QString, EntityID, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.MOVE.ERROR", error);
        }

        void setVisibility(EntityID declarator, const QString &name, VISIBILITY visibility)
        {
            Client::shared().callCommand("DECLARATOR.SET_VISIBILITY", declarator, name, visibility);
        }

        void onVisibilitySet(const std::function<void (EntityID, QString, VISIBILITY)> &then)
        {
            Client::shared().registerReply("DECLARATOR.VISIBILITY_SET", then);
        }

        void onSetVisibilityError(const std::function<void (EntityID, QString, VISIBILITY, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.SET_VISIBILITY.ERROR", error);
        }
    }

    namespace variable
    {
        void setType(EntityID variable, EntityID type)
        {
            Client::shared().callCommand("VARIABLE.SET_TYPE", variable, type);
        }

        void onTypeSet(const std::function<void (EntityID, EntityID)> &then)
        {
            Client::shared().registerReply("VARIABLE.TYPE_SET", then);
        }

        void onSetTypeError(const std::function<void (EntityID, EntityID, QString)> &error)
        {
            Client::shared().registerReply("VARIABLE.SET_TYPE.ERROR", error);
        }

        void getType(EntityID variable)
        {
            Client::shared().callCommand("VARIABLE.GET_TYPE", variable);
        }

        void onTypeGet(const std::function<void(EntityID, EntityID)> &then)
        {
            Client::shared().registerReply("VARIABLE.TYPE_GET", then);
        }

        void onGetTypeError(const std::function<void(EntityID, QString)> &error)
        {
            Client::shared().registerReply("VARIABLE.GET_TYPE.ERROR", error);
        }

        void setValue(EntityID variable, const QString &value)
        {
            Client::shared().callCommand("VARIABLE.SET_VALUE", variable, value);
        }

        void onValueSet(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("VARIABLE.VALUE_SET", then);
        }

        void onSetValueError(const std::function<void (EntityID, QString, QString)> &error)
        {
            Client::shared().registerReply("VARIABLE.SET_VALUE.ERROR", error);
        }

        void getValue(EntityID variable)
        {
            Client::shared().callCommand("VARIABLE.GET_VALUE", variable);
        }

        void onValueGet(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("VARIABLE.VALUE_GET", then);
        }

        void onGetValueError(const std::function<void (EntityID, QString)> &error)
        {
            Client::shared().registerReply("VARIABLE.GET_VALUE.ERROR", error);
        }
    }

    namespace function
    {
        void setParameter(EntityID function, const QString &paramName)
        {
            Client::shared().callCommand("FUNCTION.SET_PARAMETER", function, paramName);
        }

        void onParameterSet(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("FUNCTION.PARAMETER_SET", then);
        }

        void onSetParameterError(const std::function<void (EntityID, QString, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.SET_PARAMETER.ERROR", error);
        }

        void setReturn(EntityID function, const QString &returnName)
        {
            Client::shared().callCommand("FUNCTION.SET_RETURN", function, returnName);
        }

        void onReturnSet(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("FUNCTION.RETURN_SET", then);
        }

        void onSetReturnError(const std::function<void (EntityID, QString, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.SET_RETURN.ERROR", error);
        }

        void getParameters(EntityID function)
        {
            Client::shared().callCommand("FUNCTION.GET_PARAMETERS", function);
        }

        void onParametersGet(const std::function<void (EntityID, std::list<QString>)> &then)
        {
            Client::shared().registerReply("FUNCTION.PARAMETERS_GET", then);
        }

        void onGetParametersError(const std::function<void (EntityID, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.GET_PARAMETERS.ERROR", error);
        }

        void getReturns(EntityID function)
        {
            Client::shared().callCommand("FUNCTION.GET_RETURNS", function);
        }

        void onReturnsGet(const std::function<void (EntityID, std::list<QString>)> &then)
        {
            Client::shared().registerReply("FUNCTION.RETURNS_GET", then);
        }

        void onGetReturnsError(const std::function<void (EntityID, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.GET_RETURNS.ERROR", error);
        }

        void addInstruction(EntityID function, INSTRUCTION toadd, const std::list<EntityID> &parameters)
        {
            Client::shared().callCommand("FUNCTION.ADD_INSTRUCTION", function, toadd, parameters);
        }

        void onInstructionAdded(const std::function<void (EntityID, INSTRUCTION, std::list<EntityID>, InstructionID)> &then)
        {
            Client::shared().registerReply("FUNCTION.INSTRUCTION_ADDED", then);
        }

        void onAddInstructionError(const std::function<void (EntityID, INSTRUCTION, std::list<EntityID>, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.ADD_INSTRUCTION.ERROR", error);
        }

        void call(EntityID function, const std::map<QString, QString> &parametersValues)
        {
            Client::shared().callCommand("FUNCTION.CALL", function, parametersValues);
        }

        void onCalled(const std::function<void (EntityID, std::map<QString, QString>, std::map<QString, QString>)> &then)
        {
            Client::shared().registerReply("FUNCTION.CALLED", then);
        }

        void onCallError(const std::function<void (EntityID, std::map<QString, QString>, QString)> &error)
        {
            Client::shared().registerReply("FUNCTION.CALL.ERROR", error);
        }

        namespace instruction
        {
            void remove(EntityID function, InstructionID instruction)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.REMOVE", function, instruction);
            }

            void onRemoved(const std::function<void (EntityID, InstructionID)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.REMOVED", then);
            }

            void onRemoveError(const std::function<void (EntityID, InstructionID, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.REMOVE.ERROR", error);
            }

            void setEntryPoint(EntityID function, InstructionID instruction)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.SET_ENTRY_POINT", function, instruction);
            }

            void onEntryPointSet(const std::function<void (EntityID, InstructionID)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.ENTRY_POINT_SET", then);
            }

            void onSetEntryPointError(const std::function<void (EntityID, InstructionID, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.SET_ENTRY_POINT.ERROR", error);
            }

            void linkData(EntityID function, InstructionID instruction, const QString &inputName, InstructionID fromInstruction, const QString &output)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.LINK_DATA", function, instruction, inputName, fromInstruction, output);
            }

            void onDataLinked(const std::function<void (EntityID, InstructionID, QString, InstructionID, QString)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.DATA_LINKED", then);
            }

            void onLinkDataError(const std::function<void (EntityID, InstructionID, QString, InstructionID, QString, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.LINK_DATA.ERROR", error);
            }

            void unlinkData(EntityID function, InstructionID instruction, const QString &inputName)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.UNLINK_DATA", function, instruction, inputName);
            }

            void onDataUnlinked(const std::function<void (EntityID, InstructionID, QString)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.DATA_UNLINKED", then);
            }

            void onUnlinkDataError(const std::function<void (EntityID, InstructionID, QString, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.UNLINK_DATA.ERROR", error);
            }

            void linkExecution(EntityID function, InstructionID instruction, InstructionPin outPin, InstructionID toInstruction)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.LINK_EXECUTION", function, instruction, outPin, toInstruction);
            }

            void onExecutionLinked(const std::function<void (EntityID, InstructionID, InstructionPin, InstructionID)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.EXECUTION_LINKED", then);
            }

            void onLinkExecutionError(const std::function<void (EntityID, InstructionID, InstructionPin, InstructionID, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.LINK_EXECUTION.ERROR", error);
            }

            void unlinkExecution(EntityID function, InstructionID instruction, InstructionPin outPin)
            {
                Client::shared().callCommand("FUNCTION.INSTRUCTION.UNLINK_EXECUTION", function, instruction, outPin);
            }

            void onExecutionUnlinked(const std::function<void (EntityID, InstructionID, InstructionPin)> &then)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.EXECUTION_UNLINKED", then);
            }

            void onUnlinkExecutionError(const std::function<void (EntityID, InstructionID, InstructionPin, QString)> &error)
            {
                Client::shared().registerReply("FUNCTION.INSTRUCTION.UNLINK_EXECUTION.ERROR", error);
            }
        }
    }
}
