#ifndef COMMANDS_H
#define COMMANDS_H

#include "Scalar.h"
#include "List.h"
#include "Object.h"

#include "packagecore.h"

namespace Command {

    namespace Declare {
        using Data = Object<
            Scalar<PackageDataCom::ENTITY_CORE>,
            Scalar<uint32_t>,
            Scalar<QString>,
            Scalar<PackageDataCom::VISIBILITYCORE>
        >;

        enum Field
        {
            ENTITY_TYPE,
            CONTAINER_ID,
            NAME,
            VISIBILITY
        };

        enum Instruction_ID {
            AND,
            OR,
            DIFFERENT,
            EQUAL,
            GREATER,
            GREATER_EQUAL,
            LOWER,
            LOWER_EQUAL,
            ACCESS,
            BINARY_AND,
            BINARY_OR,
            XOR,
            ADD,
            SUB,
            DIV,
            MUL,
            MOD,
            LEFT_SHIFT,
            RIGHT_SHIFT,
            BINARY_NOT,
            NOT,
            INVERSE,
            ENUM_SPLITTER,
            GETTER,
            SETTER,
            FUNCTION_CALL,
            IF,
            WHILE,
            APPEND,
            INSERT,
            REMOVE,
            REMOVE_INDEX,
            SIZE,
            FOREACH
        };
    }
}

#endif // COMMANDS_H
