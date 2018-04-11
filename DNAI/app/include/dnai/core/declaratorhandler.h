#ifndef DNAI_CORE_DECLARATORHANDLER_H
#define DNAI_CORE_DECLARATORHANDLER_H

#include <queue>
#include <unordered_map>

#include "entitymanager.h"
#include "dnai/enums/core/coreenums.h"

namespace dnai
{
    namespace core
    {
        class DeclaratorHandler : public QObject
        {
            Q_OBJECT

        public:
            DeclaratorHandler(EntityManager &manager);
            virtual ~DeclaratorHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(enums::core::EntityID id, models::Entity &entity);
            void onEntityRemoved(enums::core::EntityID id, models::Entity &entity);

        public:
            Q_INVOKABLE void declare(models::Entity *todeclare);
            Q_INVOKABLE void remove(const models::Entity *toremove);
            void move(const models::Entity &tomove, const models::Entity &newparent);
            void rename(const models::Entity &torename, QString const &newname);
            void setVisibility(const models::Entity &entity, enums::core::VISIBILITY visibility);

        private:
            models::Entity *popDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, QString const &name);
            models::Entity *findEntity(enums::core::EntityID declarator, QString const &name, bool pop = false);

        private:
            void onDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, QString const &name, enums::core::VISIBILITY visibility, enums::core::EntityID declared);
            void onDeclareError(enums::core::EntityID declarator, enums::core::ENTITY type, QString const &name, enums::core::VISIBILITY visibility, QString const &message);

            void onRemoved(enums::core::EntityID declarator, QString const &name);
            void onRemoveError(enums::core::EntityID declarator, QString const &name, QString const &message);

            //renamed / rename_error
            //moved / move_error
            //visibility_set / set_visibility_error

        private:
            EntityManager &manager;
            std::queue<models::Entity *> pendingDeclaration;

        private:
            using DeclaratorMap = std::unordered_map<std::string, models::Entity *>;
            using RemoveMap = std::unordered_map<enums::core::EntityID, DeclaratorMap>;

            RemoveMap removed;
        };
    }
}

#endif // DNAI_CORE_DECLARATORHANDLER_H
