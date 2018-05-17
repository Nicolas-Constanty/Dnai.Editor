#ifndef DNAI_CORE_FUNCTIONHANDLER_H
#define DNAI_CORE_FUNCTIONHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class FunctionHandler : public QObject
        {
            Q_OBJECT

        public:
            FunctionHandler(EntityManager &manager);
            ~FunctionHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &added);

        public:
            Q_INVOKABLE void setParameter(models::Entity const &function, models::Entity const &paramVar);
            Q_INVOKABLE void setReturn(models::Entity const &function, models::Entity const &returnVar);

        private:
            models::gui::declarable::Function *getFunctionData(::core::EntityID function, bool throws = false);

        private:
            void onParameterSet(::core::EntityID function, QString const &paramName);
            void onSetParameterError(::core::EntityID function, QString const &paramName, QString const &message);

            void onReturnSet(::core::EntityID function, QString const &returnName);
            void onSetReturnError(::core::EntityID function, QString const &returnName, QString const &message);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_FUNCTIONHANDLER_H
