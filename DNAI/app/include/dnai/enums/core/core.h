#ifndef DNAI_ENUMS_CORE_H
#define DNAI_ENUMS_CORE_H

#include <QObject>

namespace dnai {
    namespace enums {
        inline namespace core {
            Q_NAMESPACE
            /**
             * \brief List of available commands in core.dll
             */
            enum COMMANDS : qint32
            {
                //ENTITY
                DECLARE = 0,
                REMOVE,
                RENAME,
                MOVE,
                CHANGE_VISIBILITY,
                //VARIABLE
                SET_VARIABLE_VALUE,
                GET_VARIABLE_VALUE,
                SET_CONTEXT_PARENT,
                //ENUM
                SET_ENUMERATION_TYPE,
                SET_ENUMERATION_VALUE,
                GET_ENUMERATION_VALUE,
                REMOVE_ENUMERATION_VALUE,
                //CLASS
                ADD_CLASS_ATTRIBUTE,
                RENAME_CLASS_ATTRIBUTE,
                REMOVE_CLASS_ATTRIBUTE,
                ADD_CLASS_MEMBER_FUNCTION,
                //LIST
                SET_LIST_TYPE,
                //INSTRUCTION
                CALL_FUNCTION,
                SET_FUNCTION_PARAMETER,
                SET_FUNCTION_RETURN,
                SET_FUNCTION_ENTRY_POINT,
                REMOVE_FUNCTION_INSTRUCTION,
                ADD_INSTRUCTION,
                LINK_INSTRUCTION_EXECUTION,
                LINK_INSTRUCTION_DATA,
                SET_INSTRUCTION_INPUT_VALUE,
                UNLINK_INSTRUCTION_FLOW,
                UNLINK_INSTRUCTION_INPUT
            };
            Q_ENUM_NS(COMMANDS)
            // THESE STRUCTS ARE FOR DEBUG PURPOSE, YOU CAN USED THEM TO ITERATE THROW A COMMAND TYPE
	        /**
             * \brief Allow to iterate through Entity commands
             */
            struct EntityCommands
            {
                static const qint32 begin = COMMANDS::DECLARE;
                static const qint32 end = COMMANDS::CHANGE_VISIBILITY;
            };
			/**
			* \brief Allow to iterate through Variable commands
			*/
            struct VariableCommands
            {
                static const qint32 begin = COMMANDS::SET_VARIABLE_VALUE;
                static const qint32 end = COMMANDS::SET_CONTEXT_PARENT;
            };
			/**
			* \brief Allow to iterate through Enum commands
			*/
            struct EnumCommands
            {
                static const qint32 begin = COMMANDS::SET_ENUMERATION_TYPE;
                static const qint32 end = COMMANDS::REMOVE_ENUMERATION_VALUE;
            };
			/**
			* \brief Allow to iterate through Class commands
			*/
            struct ClassCommands
            {
                static const qint32 begin = COMMANDS::ADD_CLASS_ATTRIBUTE;
                static const qint32 end = COMMANDS::ADD_CLASS_MEMBER_FUNCTION;
            };
			/**
			* \brief Allow to iterate through Instruction commands
			*/
            struct InstructionCommands
            {
                static const qint32 begin = COMMANDS::CALL_FUNCTION;
                static const qint32 end = COMMANDS::UNLINK_INSTRUCTION_INPUT;
            };
			/**
			* \brief Allow to iterate through List commands
			*/
            struct ListCommands
            {
                static const qint32 begin = COMMANDS::SET_LIST_TYPE;
                static const qint32 end = COMMANDS::SET_LIST_TYPE;
            };

	        /**
             * \brief List of available entity in core.dll
             */
            enum ENTITY
            {
                UNDEFINED = -1,
                CONTEXT,
                VARIABLE,
                FUNCTION,
                DATA_TYPE,
                ENUM_TYPE,
                OBJECT_TYPE,
                LIST_TYPE
            };

	        /**
             * \brief List of available replies in core.dll
             */
            enum REPLIES
            {
                ENTITY_DECLARED,
                ENTITY_REMOVED,
                VARIABLE_VALUE_GET,
                VARIABLE_TYPE_GET,
                ENUMERATION_VALUE_GET,
                CLASS_MEMBER_FUNCTION_ADDED,
                FUNCTION_CALLED,
                INSTRUCTION_ADDED,
                ERROR_OCCURRED
            };

	        /**
             * \brief List of available visibility in core.dll
             */
            enum VISIBILITY
            {
                PUBLIC,
                PRIVATE,
                PROTECTED
            };
            Q_ENUM_NS(ENTITY)
            Q_ENUM_NS(REPLIES)
            Q_ENUM_NS(VISIBILITY)
        }
    }
}

#endif // DNAI_ENUMS_CORE_H
