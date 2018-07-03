#ifndef DNAI_CORE_INSTRUCTIONHANDLER_H
#define DNAI_CORE_INSTRUCTIONHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class InstructionHandler : public QObject
        {
            Q_OBJECT

        public:
            InstructionHandler(EntityManager &manager);
            ~InstructionHandler() = default;

        public:
            void setup();

        public:
            Q_INVOKABLE void linkData(quint32 function, quint32 instruction, QString const &input, quint32 fromInstruction, QString const &output, bool save = true);
            Q_INVOKABLE void unlinkData(quint32 function, quint32 instruction, QString const &input, bool save = true);
            Q_INVOKABLE void linkExecution(quint32 function, quint32 instruction, quint32 outPin, quint32 toInstruction, bool save = true);
            Q_INVOKABLE void unlinkExecution(quint32 function, quint32 instruction, quint32 outPin, bool save = true);
            Q_INVOKABLE void setInputValue(quint32 function, quint32 instruction, QString const &input, QString const &value, bool save = true);

            void onDataLinked(quint32 function, quint32 from, QString const &output, quint32 to, QString const &input);
            void onLinkDataError(quint32 function, quint32 from, QString const &output, quint32 to, QString const &input, QString const &message);

            void onDataUnlinked(quint32 function, quint32 instruction, QString const &input);
            void onUnlinkDataError(quint32 function, quint32 instruction, QString const &input, QString const &message);

            void onExecutionLinked(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction);
            void onLinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, quint32 toInstruction, QString const &message);

            void onExecutionUnlinked(quint32 function, quint32 instruction, quint32 outpin);
            void onUnlinkExecutionError(quint32 function, quint32 instruction, quint32 outpin, QString const &message);

            void onInputValueSet(quint32 function, quint32 instruction, QString const &input, QString const &value);
            void onSetInputValueError(quint32 function, quint32 instruction, QString const &input, QString const &value, QString const &msg);

        signals:
            /*
             * onRemoved
             */
            void dataLinked(dnai::models::Entity *func, dnai::models::gui::Instruction *from, QString output, dnai::models::gui::Instruction *to, QString input);
            void dataUnlinked(dnai::models::Entity *func, dnai::models::gui::Instruction *instruction, QString input);
            void executionLinked(dnai::models::Entity *func, dnai::models::gui::Instruction *from, quint32 outPin, dnai::models::gui::Instruction *to);
            void executionUnlinked(dnai::models::Entity *func, dnai::models::gui::Instruction *from, quint32 outPin);
            void inputValueSet(dnai::models::Entity *func, dnai::models::gui::Instruction *instruction, QString input, QString value);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_INSTRUCTIONHANDLER_H
