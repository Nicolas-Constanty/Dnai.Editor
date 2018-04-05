#ifndef DNAI_CORE_PROJECTHANDLER_H
#define DNAI_CORE_PROJECTHANDLER_H

#include <QObject>

#include "dnai/project.h"
#include "entitymanager.h"

namespace dnai
{
    namespace core
    {
        class ProjectHandler : public QObject
        {
            Q_OBJECT

        public:
            ProjectHandler(EntityManager &manager);
            virtual ~ProjectHandler() = default;

        public:
            void setup();

        public:
            Q_INVOKABLE void create(const dnai::Project &tocreate);

        public:
            size_t getNbProject() const;

        private:
            EntityManager &manager;
            size_t nbproject;
        };
    }
}

#endif // DNAI_CORE_PROJECTHANDLER_H
