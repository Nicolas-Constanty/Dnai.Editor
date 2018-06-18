#ifndef DNAI_CORE_FUNCTIONHANDLER_H
#define DNAI_CORE_FUNCTIONHANDLER_H

#include <queue>
#include <map>

#include <QObject>

#include "entitymanager.h"

#include "instructionhandler.h"

namespace dnai
{
    namespace gcore
    {
        class FunctionHandler : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(InstructionHandler *instruction READ instruction)

        public:
            FunctionHandler(EntityManager &manager);
            ~FunctionHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &added);
            void onEntityRemoved(::core::EntityID id, models::Entity &removed);

        public:
            Q_INVOKABLE void pendingParameter(quint32 func, QString const &paramName);
            Q_INVOKABLE void pendindRemoveParam(quint32 func, QString const &paramName);

        public:
            Q_INVOKABLE void pendingReturn(quint32 func, QString const &returnName);
            Q_INVOKABLE void pendingRmReturn(quint32 func, QString const &returnName);

        public:
            Q_INVOKABLE void setEntryPoint(quint32 function, quint32 instruction, bool save = true) const;
            Q_INVOKABLE void setParameter(quint32 func, QString const &paramName, bool save = true) const;
            Q_INVOKABLE void setReturn(quint32 func, QString const &retName, bool save = true) const;
            Q_INVOKABLE void addInstruction(quint32 func, quint32 instrType, QList<quint32> const &arguments, bool save = true) const;

        private:
            models::gui::declarable::Function *getFunctionData(::core::EntityID function, bool throws = false) const;

        private:
            void refreshPendingFunctionInstructions();

        private:
            void onEntryPointSet(quint32 function, quint32 instruction);
            void onSetEntryPointError(quint32 function, quint32 instruction, QString const &message) const;

            void onParameterSet(::core::EntityID function, QString const &paramName);
            void onSetParameterError(::core::EntityID function, QString const &paramName, QString const &message) const;

            void onReturnSet(::core::EntityID function, QString const &returnName);
            void onSetReturnError(::core::EntityID function, QString const &returnName, QString const &message);

            void onInstructionAdded(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, ::core::InstructionID instruction);
            void onAddInstructionError(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, QString const &messsage);

        signals:
            void instructionAdded(models::Entity *function, models::gui::Instruction *instruction);
            void addInstructionError(quint32 func, quint32 instrType, QList<quint32> const &args, QString const &msg);
            void entryPointSet(models::Entity *func, models::gui::Instruction *entry);

        private:
            EntityManager &manager;

        public:
            InstructionHandler *instruction();

        private:
            InstructionHandler m_instruction;

        private:
            //this queue is used to set a variable as parameter when its added
            std::queue<std::pair<quint32, QString>> pendingParams;
            //this queue is when a variable is identified to be set as a parameter
            std::queue<models::Entity *> params;
            //this queue is when a parameter is removed
            std::queue<std::pair<quint32, QString>> pendingRmParam;

        private:
            //this queue is used to set a variable as return when its added
            std::queue<std::pair<quint32, QString>> pendingRet;
            //this queue is when a variable is identified to be set as return
            std::queue<models::Entity *> returns;
            //this queue is when a return is removed
            std::queue<std::pair<quint32, QString>> pendingRmRet;

        private:
            //this queue is used to save an instruction that has to be set
            std::queue<models::gui::Instruction *> pendingInstruction;

            //this queue is used to try to declare instructions once an entity is added
            std::list<models::Entity *> pendingFunctionInstructions;
        };
    }
}

#endif // DNAI_CORE_FUNCTIONHANDLER_H
