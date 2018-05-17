#ifndef DNAI_CORE_ENTITYMANAGER_H
#define DNAI_CORE_ENTITYMANAGER_H

#include <unordered_map>

#include <QObject>

#include "core.h"
#include "dnai/models/entity.h"

namespace dnai
{
    namespace gcore
    {
        class EntityManager : public QObject
        {
            Q_OBJECT

        private:
            using EntityMap = std::unordered_map<::core::EntityID, models::Entity *>;

        public:
            EntityManager() = default;
            ~EntityManager() = default;

        signals:
            void entityAdded(::core::EntityID id, models::Entity &entity);
            void entityRemoved(::core::EntityID id, models::Entity &entity);

        public:
            void addEntity(::core::EntityID id, models::Entity &entity);
            void removeEntity(::core::EntityID id);

            bool contains(::core::EntityID id) const;

            const models::Entity &getEntity(::core::EntityID id) const;
            models::Entity &getEntity(::core::EntityID id);

            const models::Entity &operator[](::core::EntityID id) const;
            models::Entity &operator[](::core::EntityID id);

        private:
            EntityMap entities;

            /*
             * Iterator
             */
        public:
            class iterator : public std::iterator<std::bidirectional_iterator_tag, models::Entity>
            {
            private:
                friend class EntityManager;

                iterator(typename EntityMap::iterator const &it);

            public:
                iterator() = default;
                iterator(iterator const &ref);
                ~iterator() = default;
                iterator &operator=(iterator const &ref);

            public:
                iterator &operator++();
                iterator operator++(int);
                bool operator==(iterator const &ref) const;
                bool operator!=(iterator const &ref) const;
                reference operator*() const;
                pointer operator->() const;

            private:
                typename EntityMap::iterator it;
            };

            iterator begin()
            {
                return iterator(entities.begin());
            }

            iterator end()
            {
                return iterator(entities.end());
            }

            /*
             * Const iterator
             */
        public:
            class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const models::Entity>
            {
            private:
                friend class EntityManager;

                const_iterator(typename EntityMap::const_iterator const &it);

            public:
                const_iterator() = default;
                const_iterator(const_iterator const &ref);
                ~const_iterator() = default;
                const_iterator &operator=(const_iterator const &ref);

            public:
                const_iterator &operator++();
                const_iterator operator++(int);
                bool operator==(const_iterator const &ref) const;
                bool operator!=(const_iterator const &ref) const;
                reference operator*() const;
                pointer operator->() const;

            private:
                typename EntityMap::const_iterator it;
            };

            const_iterator begin() const
            {
                return const_iterator(entities.begin());
            }

            const_iterator end() const
            {
                return const_iterator(entities.end());
            }
        };
    }
}

#endif // ENTITYMANAGER_H
