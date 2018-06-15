#ifndef DNAI_CORE_OBJECTHANDLER_H
#define DNAI_CORE_OBJECTHANDLER_H

#include <QObject>

#include "entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        class ObjectHandler : public QObject
        {
            Q_OBJECT

        public:
            ObjectHandler(EntityManager &manager);
            ~ObjectHandler() = default;

        public:
            void setup();

        public:
            Q_INVOKABLE void addAttribute(quint32 obj, QString name, quint32 type, qint32 visi, bool save = true);

        private:
            void onAttributeAdded(EntityID obj, QString name, EntityID type, VISIBILITY visi);
            void onAddAttributeError(EntityID obj, QString name, EntityID type, VISIBILITY visi, QString msg);

        signals:
            void attributeAdded(models::Entity *obj, QString name, models::Entity *type, VISIBILITY visi);

        private:
            EntityManager &manager;

        };
    }
}

#endif // DNAI_CORE_OBJECTHANDLER_H
