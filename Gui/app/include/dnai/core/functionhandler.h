#ifndef DNAI_CORE_FUNCTIONHANDLER_H
#define DNAI_CORE_FUNCTIONHANDLER_H

#include <queue>
#include <map>

#include <QObject>
#include <QStack>

#include "entitymanager.h"

#include "instructionhandler.h"

namespace dnai
{
    namespace gcore
    {
        class FunctionHandler : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(InstructionHandler *instruction READ instruction CONSTANT)

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
            Q_INVOKABLE void removeInstruction(quint32 func, quint32 instruction, bool save = true);

        private:
            models::gui::declarable::Function *getFunctionData(::core::EntityID function, bool throws = false) const;
            std::list<quint32> getConstructionList(models::gui::Instruction *instr) const;
            QList<QString> getLinkedEntities(std::list<quint32> const &construction) const;

        private:
            models::gui::Instruction *createInstruction(qint32 type, std::list<quint32> const &constrution = std::list<quint32>());

        private:
            void refreshPendingFunctionInstructions();
            QString getInstructionHash(QUuid funcguid, qint32 type) const;

        public:
            void rebuildInstructions(QList<models::gui::Instruction *> instructions);

        public:
            void onEntryPointSet(quint32 function, quint32 instruction);
            void onSetEntryPointError(quint32 function, quint32 instruction, QString const &message) const;

            void onParameterSet(::core::EntityID function, QString const &paramName);
            void onSetParameterError(::core::EntityID function, QString const &paramName, QString const &message) const;

            void onReturnSet(::core::EntityID function, QString const &returnName);
            void onSetReturnError(::core::EntityID function, QString const &returnName, QString const &message);

            void onInstructionAdded(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, ::core::InstructionID instruction);
            void onAddInstructionError(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, QString const &messsage);

            void onInstructionRemoved(::core::EntityID function, ::core::InstructionID instruction);
            void onRemoveInstructionError(::core::EntityID funtion, ::core::InstructionID instruction, QString msg);

        signals:
            void instructionAdded(dnai::models::Entity *func, dnai::models::gui::Instruction *instruction);
            void addInstructionError(quint32 func, quint32 instrType, QList<quint32> const &args, QString const &msg);
            void instructionRemoved(dnai::models::Entity *func, dnai::models::gui::Instruction *instruction);
            void entryPointSet(dnai::models::Entity *func, dnai::models::gui::Instruction *entry);
            void parameterSet(dnai::models::Entity *func, QString param);
            void returnSet(dnai::models::Entity *func, QString ret);

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

        private:
            //map that contains removed instructions
            QHash<QString, QStack<models::gui::Instruction *>> removedInstructions;
            //map that contains added instructions
            QHash<QString, QStack<models::gui::Instruction *>> addedInstructions;

        private:
            //instruction function map
            QHash<models::gui::Instruction *, models::Entity *> instructionsFunction;

        private:
            //map to store instruction that are currently rebuilding
            QSet<models::gui::Instruction *> pendingRebuild;
        };
    }
}

#endif // DNAI_CORE_FUNCTIONHANDLER_H
