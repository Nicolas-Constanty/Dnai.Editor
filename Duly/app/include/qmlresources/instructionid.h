#ifndef INSTRUCTION_ID
#define INSTRUCTION_ID

#include <QObject>

namespace duly_gui {
namespace qmlresources {
class QInstructionID : public QObject
{
    Q_OBJECT
public:
    QInstructionID(QObject *parent = nullptr) : QObject(parent) {}
    ~QInstructionID() {}

    enum Instruction_ID
    {
        AND = 0,
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
    Q_ENUM(Instruction_ID)
};
}
}

#endif // INSTRUCTION_ID
