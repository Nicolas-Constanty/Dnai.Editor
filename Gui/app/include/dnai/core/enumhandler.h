#ifndef DNAI_CORE_ENUMHANDLER_H
#define DNAI_CORE_ENUMHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class EnumHandler : public QObject
        {
            Q_OBJECT

        public:
            EnumHandler(EntityManager &manager);
            ~EnumHandler() = default;

        public:
            void setup();

        signals:
            void valueSet(dnai::models::Entity *entity, QString const &name, QJsonValue const &value);
            void valueRemoved(dnai::models::Entity *entity, QString const &name);

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);

        public:
            Q_INVOKABLE void setValue(::core::EntityID entity, QString const &name, QJsonValue const &value);
            Q_INVOKABLE void removeValue(::core::EntityID entity, QString const &name);

        private:
            void onValueSet(::core::EntityID enumeration, QString const &name, QString const &value);
            void onSetValueError(::core::EntityID enumeration, QString const &name, QString const &value, QString const &message);

            void onValueRemoved(::core::EntityID enumeration, QString const &name);
            void onRemoveValueError(::core::EntityID enumeration, QString const &name, QString const &message);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_ENUMHANDLER_H
