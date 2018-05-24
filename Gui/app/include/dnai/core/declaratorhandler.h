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
            Q_INVOKABLE void declare(quint32 parentId, qint32 type, QString name, qint32 visibility = static_cast<qint32>(::core::VISIBILITY::PUBLIC));
            Q_INVOKABLE void remove(quint32 parentId, QString const &name);
            void move(const models::Entity &tomove, const models::Entity &newparent);
            void rename(const models::Entity &torename, QString const &newname);
            void setVisibility(const models::Entity &entity, ::core::VISIBILITY visibility);

        private:
            models::Entity *findEntity(::core::EntityID declarator, QString const &name);

        private:
            void onDeclared(::core::EntityID declarator, ::core::ENTITY type, QString const &name, ::core::VISIBILITY visibility, ::core::EntityID declared);
            void onDeclareError(::core::EntityID declarator, ::core::ENTITY type, QString const &name, ::core::VISIBILITY visibility, QString const &message);

            void onRemoved(::core::EntityID declarator, QString const &name);
            void onRemoveError(::core::EntityID declarator, QString const &name, QString const &message);

            //renamed / rename_error
            //moved / move_error
            //visibility_set / set_visibility_error

        private:
            EntityManager &manager;
            std::queue<models::Entity *> pendingDeclaration;

        private:
            std::unordered_map<std::string, models::Entity *> removedEntities;
        };
    }
}

#endif // DNAI_CORE_DECLARATORHANDLER_H
