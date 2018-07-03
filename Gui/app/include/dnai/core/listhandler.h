#ifndef DNAI_CORE_LISTHANDLER_H
#define DNAI_CORE_LISTHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class ListHandler : public QObject
        {
            Q_OBJECT

        public:
            ListHandler(EntityManager &manager);
            ~ListHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);

        private:
            void refreshTypes();

        public:
            Q_INVOKABLE void setType(quint32 listId, quint32 listType, bool save = true);

        private:
            void onTypeSet(EntityID listId, EntityID listType);
            void onSetTypeError(EntityID listId, EntityID listType, QString msg);

        signals:
            void typeSet(dnai::models::Entity *list, dnai::models::Entity *type);

        private:
            EntityManager &manager;

        private:
            std::list<models::Entity *> pendingLists;
        };
    }
}

#endif // DNAI_CORE_LISTHANDLER_H
