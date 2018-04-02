#include <functional>

#include "dnai/core/declaratorhandler.h"

//using namespace std;
using namespace std::placeholders;

namespace dnai
{
    namespace core
    {
        DeclaratorHandler::DeclaratorHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void DeclaratorHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(enums::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(enums::core::EntityID,models::Entity&)));


            ::core::declarator::onDeclared(std::bind(&DeclaratorHandler::onDeclared, this, _1, _2, _3, _4, _5));
            ::core::declarator::onDeclareError(std::bind(&DeclaratorHandler::onDeclareError, this, _1, _2, _3, _4, _5));
            ::core::declarator::onRemoved(std::bind(&DeclaratorHandler::onRemoved, this, _1, _2));
            ::core::declarator::onRemoveError(std::bind(&DeclaratorHandler::onRemoveError, this, _1, _2, _3));
        }

        void DeclaratorHandler::onEntityAdded(enums::core::EntityID id, models::Entity &entity)
        {
            //declare its children
        }

        void DeclaratorHandler::onDeclared(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, enums::core::EntityID declared)
        {
            //add it to manager
        }

        void DeclaratorHandler::onDeclareError(enums::core::EntityID declarator, enums::core::ENTITY type, const QString &name, enums::core::VISIBILITY visibility, const QString &message)
        {
            //remove command
        }

        void DeclaratorHandler::onRemoved(enums::core::EntityID declarator, const QString &name)
        {
            //remove from manager
        }

        void DeclaratorHandler::onRemoveError(enums::core::EntityID declarator, const QString &name, const QString &message)
        {
            //remove command
        }
    }
}
