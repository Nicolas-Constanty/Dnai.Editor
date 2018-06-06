#include "dnai/core/entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        EntityManager::EntityManager()
        {
            addEntity(1, *(new models::Entity(new models::gcore::Entity("Boolean", core::ENTITY::DATA_TYPE, 1))));
            addEntity(2, *(new models::Entity(new models::gcore::Entity("Integer", core::ENTITY::DATA_TYPE, 2))));
            addEntity(3, *(new models::Entity(new models::gcore::Entity("Floating", core::ENTITY::DATA_TYPE, 3))));
            addEntity(4, *(new models::Entity(new models::gcore::Entity("Character", core::ENTITY::DATA_TYPE, 4))));
            addEntity(5, *(new models::Entity(new models::gcore::Entity("String", core::ENTITY::DATA_TYPE, 5))));
        }

        void EntityManager::addEntity(::core::EntityID id, models::Entity &entity)
        {
            entity.setId(id);
            entities[id] = &entity;
            emit entityAdded(id, entity);
        }

        void EntityManager::removeEntity(::core::EntityID id)
        {
            typename EntityMap::iterator it = entities.find(id);
            models::Entity &tosend = *it->second;

            entities.erase(it);
            emit entityRemoved(id, tosend);
        }

        bool EntityManager::contains(::core::EntityID id) const
        {
            return entities.find(id) != entities.end();
        }

        const models::Entity &EntityManager::getEntity(::core::EntityID id) const
        {
            return *entities.at(id);
        }

        models::Entity &EntityManager::getEntity(::core::EntityID id)
        {
            return *entities.at(id);
        }

        const models::Entity *EntityManager::findByFullname(const QString &fullName) const
        {
            for (const models::Entity &curr : *this) {
                if (curr.fullName() == fullName) {
                    return &curr;
                }
            }
            return nullptr;
        }

        models::Entity *EntityManager::findByFullname(const QString &fullName)
        {
            for (models::Entity &curr : *this) {
                if (curr.fullName() == fullName) {
                    return &curr;
                }
            }
            return nullptr;
        }

        const models::Entity &EntityManager::operator [](::core::EntityID id) const
        {
            return getEntity(id);
        }

        models::Entity &EntityManager::operator [](::core::EntityID id)
        {
            return getEntity(id);
        }

        /*
         * Iterator
         */
        EntityManager::iterator::iterator(const EntityMap::iterator &it) :
            it(it)
        {

        }

        EntityManager::iterator::iterator(const iterator &ref) :
            it(ref.it)
        {

        }

        EntityManager::iterator &EntityManager::iterator::operator =(iterator const &ref)
        {
            it = ref.it;
            return *this;
        }

        EntityManager::iterator &EntityManager::iterator::operator ++()
        {
            ++it;
            return *this;
        }

        EntityManager::iterator EntityManager::iterator::operator ++(int)
        {
            iterator cpy(*this);

            ++it;
            return cpy;
        }

        bool EntityManager::iterator::operator ==(iterator const &ref) const
        {
            return ref.it == it;
        }

        bool EntityManager::iterator::operator !=(iterator const &ref) const
        {
            return ref.it != it;
        }

        EntityManager::iterator::reference EntityManager::iterator::operator *() const
        {
            return *it->second;
        }

        EntityManager::iterator::pointer EntityManager::iterator::operator ->() const
        {
            return it->second;
        }

        /*
         * Const iterator
         */

        EntityManager::const_iterator::const_iterator(const EntityMap::const_iterator &it) :
            it(it)
        {

        }

        EntityManager::const_iterator::const_iterator(const const_iterator &ref) :
            it(ref.it)
        {

        }

        EntityManager::const_iterator &EntityManager::const_iterator::operator =(const_iterator const &ref)
        {
            it = ref.it;
            return *this;
        }

        EntityManager::const_iterator &EntityManager::const_iterator::operator ++()
        {
            ++it;
            return *this;
        }

        EntityManager::const_iterator EntityManager::const_iterator::operator ++(int)
        {
            const_iterator cpy(*this);

            ++it;
            return cpy;
        }

        bool EntityManager::const_iterator::operator ==(const_iterator const &ref) const
        {
            return ref.it == it;
        }

        bool EntityManager::const_iterator::operator !=(const_iterator const &ref) const
        {
            return ref.it != it;
        }

        EntityManager::const_iterator::reference EntityManager::const_iterator::operator *() const
        {
            return *it->second;
        }

        EntityManager::const_iterator::pointer EntityManager::const_iterator::operator ->() const
        {
            return it->second;
        }
    }
}
