#ifndef DNAI_CORE_ENUMHANDLER_H
#define DNAI_CORE_ENUMHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace core
    {
        class EnumHandler : public QObject
        {
            Q_OBJECT

        public:
            EnumHandler(EntityManager &manager);
            ~EnumHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(enums::core::EntityID id, models::Entity &entity);

        public:
            Q_INVOKABLE void setValue();
            Q_INVOKABLE void removeValue();

        private:
            void onValueSet(enums::core::EntityID enumeration, QString const &name);
            void onSetValueError(enums::core::EntityID enumeration, QString const &name, QString const &message);

            void onValueRemoved(enums::core::EntityID enumeration, QString const &name);
            void onRemoveValueError(enums::core::EntityID enumeration, QString const &name, QString const &message);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_ENUMHANDLER_H
