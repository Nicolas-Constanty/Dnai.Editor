#ifndef DNAI_ENUM_INSTRUCTION_ID
#define DNAI_ENUM_INSTRUCTION_ID

#include <QObject>

namespace dnai {
namespace enums {
class QInstructionID : public QObject
{
    Q_OBJECT
public:
    QInstructionID(QObject *parent = nullptr) : QObject(parent) {}
    ~QInstructionID() {}

	/**
     * \brief List of instruction available in core.dll
     */
    enum Instruction_ID : qint32
    {
		UNDEFINED = -1,
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
        FOREACH,
        GET_ATTRIBUTES,
        SET_ATTRIBUTES,
        BREAK,
        CONTINUE,
        CLEAR,
        FILL,
        SET_VALUE_AT,
        RETURN
    };
    Q_ENUM(Instruction_ID)
};
}
}

#endif // DNAI_ENUM_INSTRUCTION_ID
