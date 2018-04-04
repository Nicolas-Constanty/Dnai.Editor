#include "dnai/core/entitymanager.h"

namespace dnai
{
    namespace core
    {
        void EntityManager::addEntity(enums::core::EntityID id, models::Entity &entity)
        {
            entity.setId(id);
            entities[id] = &entity;
            emit entityAdded(id, entity);
        }

        void EntityManager::removeEntity(enums::core::EntityID id)
        {
            typename EntityMap::iterator it = entities.find(id);
            models::Entity &tosend = *it->second;

            entities.erase(it);
            emit entityRemoved(id, tosend);
        }

        bool EntityManager::contains(enums::core::EntityID id) const
        {
            return entities.find(id) != entities.end();
        }

        const models::Entity &EntityManager::getEntity(enums::core::EntityID id) const
        {
            return *entities.at(id);
        }

        models::Entity &EntityManager::getEntity(enums::core::EntityID id)
        {
            return *entities.at(id);
        }

        const models::Entity &EntityManager::operator [](enums::core::EntityID id) const
        {
            return getEntity(id);
        }

        models::Entity &EntityManager::operator [](enums::core::EntityID id)
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
