#ifndef DNAI_CORE_FUNCTIONHANDLER_H
#define DNAI_CORE_FUNCTIONHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace core
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
            void onEntityAdded(enums::core::EntityID id, models::Entity &added);

        public:
            Q_INVOKABLE void setParameter(models::Entity const &function, models::Entity const &paramVar);
            Q_INVOKABLE void setReturn(models::Entity const &function, models::Entity const &returnVar);

        private:
            models::gui::declarable::Function *getFunctionData(enums::core::EntityID function, bool throws = false);

        private:
            void onParameterSet(enums::core::EntityID function, QString const &paramName);
            void onSetParameterError(enums::core::EntityID function, QString const &paramName, QString const &message);

            void onReturnSet(enums::core::EntityID function, QString const &returnName);
            void onSetReturnError(enums::core::EntityID function, QString const &returnName, QString const &message);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_FUNCTIONHANDLER_H
