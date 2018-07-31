#include "dnai/core/entitymanager.h"

namespace dnai
{
    namespace gcore
    {
        void EntityManager::setup()
        {
            addEntity(1, *(new models::Entity(new models::gcore::Entity("Boolean", core::ENTITY::DATA_TYPE, 1), nullptr, nullptr, "{907ad50a-8f54-51ea-8c68-479d1d90a699}")));
            addEntity(2, *(new models::Entity(new models::gcore::Entity("Integer", core::ENTITY::DATA_TYPE, 2), nullptr, nullptr, "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}")));
            addEntity(3, *(new models::Entity(new models::gcore::Entity("Floating", core::ENTITY::DATA_TYPE, 3), nullptr, nullptr, "{0db5b2f0-5384-5579-9433-f92bbf306aef}")));
            addEntity(4, *(new models::Entity(new models::gcore::Entity("Character", core::ENTITY::DATA_TYPE, 4), nullptr, nullptr, "{22f34ba1-b80d-595b-b485-e1ff3d1e1283}")));
            addEntity(5, *(new models::Entity(new models::gcore::Entity("String", core::ENTITY::DATA_TYPE, 5), nullptr, nullptr, "{dd0b3137-38d0-5521-879a-1abfc6a5c664}")));
        }

        void EntityManager::addEntity(::core::EntityID id, models::Entity &entity)
        {
            entity.setId(id);
            entities[id] = &entity;
            g_entities[entity.guid()] = &entity;
            emit entityAdded(id, entity);
        }

        void EntityManager::removeEntity(::core::EntityID id)
        {
            typename EntityMap::iterator it = entities.find(id);
            models::Entity &tosend = *it->second;

            entities.erase(it);
            g_entities.remove(tosend.guid());
            emit entityRemoved(id, tosend);
        }

        bool EntityManager::contains(::core::EntityID id) const
        {
            return entities.find(id) != entities.end();
        }

        bool EntityManager::contains(const QUuid &guid) const
        {
            return g_entities.contains(guid);
        }

        const models::Entity &EntityManager::getEntity(::core::EntityID id) const
        {
            return *entities.at(id);
        }

        const models::Entity *EntityManager::getEntity(const QUuid &id) const
        {
            return g_entities.value(id, nullptr);
        }

        models::Entity &EntityManager::getEntity(::core::EntityID id)
        {
            return *entities.at(id);
        }

        models::Entity *EntityManager::getEntity(const QUuid &id)
        {
            return g_entities.value(id, nullptr);
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
