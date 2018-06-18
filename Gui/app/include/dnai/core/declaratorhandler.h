#ifndef DNAI_CORE_DECLARATORHANDLER_H
#define DNAI_CORE_DECLARATORHANDLER_H

#include <queue>
#include <unordered_map>

#include "entitymanager.h"
#include "core.h"
#include "dnai/project.h"

namespace dnai
{
    namespace gcore
    {
        class DeclaratorHandler : public QObject
        {
            Q_OBJECT

        public:
            DeclaratorHandler(EntityManager &manager);
            virtual ~DeclaratorHandler();

        public:
            void setup();

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);
            void onEntityRemoved(::core::EntityID id, models::Entity &entity);

        signals:
            void declared(dnai::models::Entity *entity);
            void removed(dnai::models::Entity *entity);
            void moved();
            void renamed();
            void visibilitySet();

        private:
            models::Entity *createEntity(::core::ENTITY type, models::Entity *parent);

        public:
            Q_INVOKABLE void declare(quint32 parentId, qint32 type, QString name, qint32 visibility = static_cast<qint32>(::core::VISIBILITY::PUBLIC), bool save = true);
            Q_INVOKABLE void remove(quint32 parentId, QString const &name, bool save = true);
            void move(const models::Entity &tomove, const models::Entity &newparent, bool save = true);
            Q_INVOKABLE void rename(quint32 parentId, QString const &name, QString const &newname, bool save = true);
            Q_INVOKABLE void setVisibility(quint32 parentId, QString const &name, qint32 visibility, bool save = true);

        private:
            models::Entity *findEntity(::core::EntityID declarator, QString const &name);

        public:
            void onDeclared(::core::EntityID declarator, ::core::ENTITY type, QString const &name, ::core::VISIBILITY visibility, ::core::EntityID declared);
            void onDeclareError(::core::EntityID declarator, ::core::ENTITY type, QString const &name, ::core::VISIBILITY visibility, QString const &message);

            void onRemoved(::core::EntityID declarator, QString const &name, std::list<EntityID> const &rmvList);
            void onRemoveError(::core::EntityID declarator, QString const &name, QString const &message);

            void onRenamed(::core::EntityID declarator, QString const &name, QString const &newname);
            void onRenameError(::core::EntityID declarator, QString const &name, QString const &newname, QString const &message);

            void onVisibilitySet(::core::EntityID declarator, QString const &name, core::VISIBILITY visibility);
            void onSetVisibilityError(core::EntityID declarator, QString const &name, core::VISIBILITY visibility, QString const &message);

            //moved / move_error

        private:
            EntityManager &manager;
            std::queue<models::Entity *> pendingDeclaration;

        private:
            std::unordered_map<std::string, models::Entity *> removedEntities;
        };
    }
}

#endif // DNAI_CORE_DECLARATORHANDLER_H
