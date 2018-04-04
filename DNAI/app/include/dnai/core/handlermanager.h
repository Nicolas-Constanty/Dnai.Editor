#ifndef DNAI_CORE_HANDLERMANAGER_H
#define DNAI_CORE_HANDLERMANAGER_H

#include "entitymanager.h"

#include "projecthandler.h"
#include "declaratorhandler.h"
#include "variablehandler.h"
#include "objecthandler.h"
#include "functionhandler.h"
#include "enumhandler.h"
#include "listhandler.h"

namespace dnai
{
    namespace core
    {
        class HandlerManager
        {
        private:
            HandlerManager();

        public:
            static HandlerManager &Instance();

        public:
            ProjectHandler &Project();
            DeclaratorHandler &Declarator();

        private:
            EntityManager m_manager;
            ProjectHandler m_project;
            DeclaratorHandler m_declarator;
        };
    }
}

#endif // DNAI_CORE_HANDLERMANAGER_H
