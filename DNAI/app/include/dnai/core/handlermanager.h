#ifndef DNAI_CORE_HANDLERMANAGER_H
#define DNAI_CORE_HANDLERMANAGER_H

#include <QObject>

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
        class HandlerManager : public QObject
        {
            Q_OBJECT

        private:
            HandlerManager();

        public:
            static HandlerManager &Instance();

        public:
            ProjectHandler &Project();
            DeclaratorHandler &Declarator();
            VariableHandler &Variable();

        private:
            EntityManager m_manager;

        private:
            ProjectHandler m_project;
            DeclaratorHandler m_declarator;
            VariableHandler m_variable;
        };
    }
}

#endif // DNAI_CORE_HANDLERMANAGER_H
