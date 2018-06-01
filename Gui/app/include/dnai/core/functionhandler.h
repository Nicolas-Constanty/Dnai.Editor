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
            Q_INVOKABLE void setParameter(quint32 func, QString const &paramName);
            Q_INVOKABLE void setReturn(quint32 func, QString const &retName);
            Q_INVOKABLE void addInstruction(quint32 func, quint32 instrType, QList<quint32> const &arguments);

        private:
            models::gui::declarable::Function *getFunctionData(::core::EntityID function, bool throws = false);

        private:
            void onParameterSet(::core::EntityID function, QString const &paramName);
            void onSetParameterError(::core::EntityID function, QString const &paramName, QString const &message);

            void onReturnSet(::core::EntityID function, QString const &returnName);
            void onSetReturnError(::core::EntityID function, QString const &returnName, QString const &message);

            void onInstructionAdded(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, ::core::InstructionID instruction);
            void onAddInstructionError(::core::EntityID function, ::core::INSTRUCTION type, std::list<::core::EntityID> const &arguments, QString const &messsage);

        signals:
            void instructionAdded(models::Entity *function, models::gui::Instruction *instruction);
            void addInstructionError(quint32 func, quint32 instrType, QList<quint32> const &args, QString const &msg);

        private:
            EntityManager &manager;

        public:
            InstructionHandler *instruction();

        private:
            InstructionHandler m_instruction;

        private:
            std::queue<std::pair<quint32, QString>> pendingParams;
            std::queue<models::Entity *> params;

            std::queue<std::pair<quint32, QString>> pendingRmParam;

        private:
            std::queue<std::pair<quint32, QString>> pendingRet;
            std::queue<models::Entity *> returns;

            std::queue<std::pair<quint32, QString>> pendingRmRet;
        };
    }
}

#endif // DNAI_CORE_FUNCTIONHANDLER_H
