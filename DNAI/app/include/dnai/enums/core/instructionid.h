#ifndef INSTRUCTION_ID
#define INSTRUCTION_ID

#include <QObject>

namespace dnai {
namespace enums {
class QInstructionID : public QObject
{
    Q_OBJECT
public:
    QInstructionID(QObject *parent = nullptr) : QObject(parent) {}
    ~QInstructionID() {}

    enum Instruction_ID
    {
        AND = (int)(0),
        OR = (int)(1),
        DIFFERENT = (int)(2),
        EQUAL = (int)(3),
        GREATER = (int)(4),
        GREATER_EQUAL = (int)(5),
        LOWER = (int)(6),
        LOWER_EQUAL = (int)(7),
        ACCESS = (int)(8),
        BINARY_AND = (int)(9),
        BINARY_OR= (int)(10),
        XOR = (int)(11),
        ADD = (int)(12),
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
    Q_ENUM(Instruction_ID)
};
}
}

#endif // INSTRUCTION_ID
