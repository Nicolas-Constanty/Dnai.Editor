#ifndef CORE_CLIENT_CORE_H
#define CORE_CLIENT_CORE_H

#include <functional>
#include <cinttypes>
#include <map>
#include <list>

#include <QString>

namespace core
{
    using EntityID = uint32_t;
    using InstructionID = uint32_t;
    using InstructionPin = uint32_t;

    enum ENTITY : int32_t
    {
        UNDEFINED = -1,
        CONTEXT = 0,
        VARIABLE = 1,
        FUNCTION = 2,
        DATA_TYPE = 3,
        ENUM_TYPE = 4,
        OBJECT_TYPE = 5,
        LIST_TYPE = 6
    };

    enum VISIBILITY
    {
        PRIVATE = 0,
        PUBLIC = 1
    };

    enum INSTRUCTION
    {

    };

    void connect(qint16 serverPort);

    namespace declarator
    {
        void declare(EntityID declarator, ENTITY type, QString const &name, VISIBILITY visibility);
        void onDeclared(std::function<void(EntityID, ENTITY, QString, VISIBILITY, EntityID)> const &then);
        void onDeclareError(std::function<void(EntityID, ENTITY, QString, VISIBILITY, QString)> const &error);

        void remove(EntityID declarator, QString const &name);
        void onRemoved(std::function<void(EntityID, QString)> const &then);
        void onRemoveError(std::function<void(EntityID, QString, QString)> const &error);

        void rename(EntityID declarator, QString const &name, QString const &newName);
        void onRenamed(std::function<void(EntityID, QString, QString)> const &then);
        void onRenameError(std::function<void(EntityID, QString, QString, QString)> const &error);

        void move(EntityID declarator, QString const &name, EntityID newParent);
        void onMoved(std::function<void(EntityID, QString, EntityID)> const &then);
        void onMoveError(std::function<void(EntityID, QString, EntityID, QString)> const &error);

        void setVisibility(EntityID declarator, QString const &name, VISIBILITY visibility);
        void onVisibilitySet(std::function<void(EntityID, QString, VISIBILITY)> const &then);
        void onSetVisibilityError(std::function<void(EntityID, QString, VISIBILITY, QString)> const &error);

        //get entity
        //get entities
    }

    namespace variable
    {
        void setType(EntityID variable, EntityID type);
        void onTypeSet(std::function<void(EntityID, EntityID)> const &then);
        void onSetTypeError(std::function<void(EntityID, EntityID, QString)> const &error);

        void getType(EntityID variable);
        void onTypeGet(std::function<void(EntityID, EntityID)> const &then);
        void onGetTypeError(std::function<void(EntityID, QString)> const &error);

        void setValue(EntityID variable, QString const &value);
        void onValueSet(std::function<void(EntityID, QString)> const &then);
        void onSetValueError(std::function<void(EntityID, QString, QString)> const &error);

        void getValue(EntityID variable);
        void onValueGet(std::function<void(EntityID, QString)> const &then);
        void onGetValueError(std::function<void(EntityID, QString)> const &error);
    }

    namespace function
    {
        void setParameter(EntityID function, QString const &paramName);
        void onParameterSet(std::function<void(EntityID, QString)> const &then);
        void onSetParameterError(std::function<void(EntityID, QString, QString)> const &error);

        void setReturn(EntityID function, QString const &returnName);
        void onReturnSet(std::function<void(EntityID, QString)> const &then);
        void onSetReturnError(std::function<void(EntityID, QString, QString)> const &error);

        void getParameters(EntityID function);
        void onParametersGet(std::function<void(EntityID, std::list<QString>)> const &then);
        void onGetParametersError(std::function<void(EntityID, QString)> const &error);

        void getReturns(EntityID function);
        void onReturnsGet(std::function<void(EntityID, std::list<QString>)> const &then);
        void onGetReturnsError(std::function<void(EntityID, QString)> const &error);

        void addInstruction(EntityID function, INSTRUCTION toadd, std::list<EntityID> const &parameters);
        void onInstructionAdded(std::function<void(EntityID, INSTRUCTION, std::list<EntityID>, InstructionID)> const &then);
        void onAddInstructionError(std::function<void(EntityID, INSTRUCTION, std::list<EntityID>, QString)> const &error);

        void call(EntityID function, std::map<QString, QString> const &parametersValues);
        void onCalled(std::function<void(EntityID, std::map<QString, QString>, std::map<QString, QString>)> const &then);
        void onCallError(std::function<void(EntityID, std::map<QString, QString>, QString)> const &error);

        namespace instruction
        {
            void remove(EntityID function, InstructionID instruction);
            void onRemoved(std::function<void(EntityID, InstructionID)> const &then);
            void onRemoveError(std::function<void(EntityID, InstructionID, QString)> const &error);

            void setEntryPoint(EntityID function, InstructionID instruction);
            void onEntryPointSet(std::function<void(EntityID, InstructionID)> const &then);
            void onSetEntryPointError(std::function<void(EntityID, InstructionID, QString)> const &error);

            void linkData(EntityID function, InstructionID instruction, QString const &inputName, InstructionID fromInstruction, QString const &output);
            void onDataLinked(std::function<void(EntityID, InstructionID, QString, InstructionID, QString)> const &then);
            void onLinkDataError(std::function<void(EntityID, InstructionID, QString, InstructionID, QString, QString)> const &error);

            void unlinkData(EntityID function, InstructionID instruction, QString const &inputName);
            void onDataUnlinked(std::function<void(EntityID, InstructionID, QString)> const &then);
            void onUnlinkDataError(std::function<void(EntityID, InstructionID, QString, QString)> const &error);

            void linkExecution(EntityID function, InstructionID instruction, InstructionPin outPin, InstructionID toInstruction);
            void onExecutionLinked(std::function<void(EntityID, InstructionID, InstructionPin, InstructionID)> const &then);
            void onLinkExecutionError(std::function<void(EntityID, InstructionID, InstructionPin, InstructionID, QString)> const &error);

            void unlinkExecution(EntityID function, InstructionID instruction, InstructionPin outPin);
            void onExecutionUnlinked(std::function<void(EntityID, InstructionID, InstructionPin)> const &then);
            void onUnlinkExecutionError(std::function<void(EntityID, InstructionID, InstructionPin, QString)> const &error);
        }
    }

    namespace enumeration
    {
        //set value
        //remove value
        //get value
        //set type
        //get type
    }

    namespace list
    {
        //set type
        //get type
    }

    namespace object
    {
        //set attribute
        //rename attribute
        //remove attribute
        //get attributes
        //get attribute
        //set function as member
    }
}

#endif // CORE_CLIENT_CORE_H
