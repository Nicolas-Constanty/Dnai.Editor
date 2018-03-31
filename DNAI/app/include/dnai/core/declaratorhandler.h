#ifndef DNAI_CORE_DECLARATORHANDLER_H
#define DNAI_CORE_DECLARATORHANDLER_H

#include "entitymanager.h"
#include "icorehandler.h"
#include "core.h"

namespace dnai
{
    namespace core
    {
        class DeclaratorHandler : public QObject, public ICoreHandler
        {
            Q_OBJECT

        public:
            DeclaratorHandler(EntityManager &manager);
            virtual ~DeclaratorHandler() = default;

        public:
            void setup() override;

        public slots:
            void onEntityAdded(enums::core::EntityID id, models::Entity &entity);

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
        };
    }
}

#endif // DNAI_CORE_DECLARATORHANDLER_H
