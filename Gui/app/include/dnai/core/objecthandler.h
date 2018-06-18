#ifndef DNAI_CORE_OBJECTHANDLER_H
#define DNAI_CORE_OBJECTHANDLER_H

#include <queue>
#include <unordered_map>
#include <unordered_set>

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

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);
            void onEntityRemoved(::core::EntityID id, models::Entity &entity);
            void onParameterSet(models::Entity *func, QString paramName);

        public:
            Q_INVOKABLE void addAttribute(quint32 obj, QString name, quint32 type, qint32 visi, bool save = true);
            Q_INVOKABLE void removeAttribute(quint32 obj, QString name, bool save = true);
            Q_INVOKABLE void renameAttribute(quint32 obj, QString name, QString newName, bool save = true);
            Q_INVOKABLE void setAttributeType(quint32 obj, QString name, quint32 type, bool save = true);
            Q_INVOKABLE void setFunctionAsMember(quint32 obj, QString name, bool save = true);
            Q_INVOKABLE void setFunctionAsStatic(quint32 obj, QString name, bool save = true);

        private:
            bool isAttributePending(EntityID obj, QString const &name) const;
            void removePendingAttribute(EntityID obj, QString const &name);
            void refreshPendingAttributes(EntityID id);

        private:
            void onAttributeAdded(EntityID obj, QString name, EntityID type, VISIBILITY visi);
            void onAddAttributeError(EntityID obj, QString name, EntityID type, VISIBILITY visi, QString msg);

            void onAttributeRemoved(EntityID obj, QString name);
            void onRemoveAttributeError(EntityID obj, QString name, QString msg);

            void onAttributeRenamed(EntityID obj, QString name, QString newName);
            void onRenameAttributeError(EntityID obj, QString name, QString newName, QString msg);

            void onFunctionSetAsMember(EntityID obj, QString name, EntityID thisId);
            void onSetFunctionAsMemberError(EntityID obj, QString name, QString msg);

        signals:
            void attributeAdded(models::Entity *obj, QString name, models::Entity *type, VISIBILITY visi);
            void attributeRemoved(models::Entity *obj, QString name);
            void attributeRenamed(models::Entity *obj, QString name, QString newName);
            void functionSetAsMember(models::Entity *obj, QString name, models::Entity *thisParam);
            void functionSetAsStatic(models::Entity *obj, QString name);

        private:
            EntityManager &manager;

        private:
            std::queue<std::function<void()>> m_pendingAdd;

        private:
            using AttrMap = std::unordered_map<models::Entity *, QList<QString>>;
            AttrMap m_pendingAttributes;

        private:
            using AttrSet = std::unordered_set<std::string>;
            AttrSet m_attributeAdded;
        };
    }
}

#endif // DNAI_CORE_OBJECTHANDLER_H
