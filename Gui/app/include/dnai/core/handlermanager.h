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
    namespace gcore
    {
        class HandlerManager : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(ProjectHandler *project READ project)
            Q_PROPERTY(DeclaratorHandler *declarator READ declarator)
            Q_PROPERTY(VariableHandler *variable READ variable)
            Q_PROPERTY(EnumHandler *enumeration READ enumeration)

        private:
            HandlerManager();

        public:
            static HandlerManager &Instance();

            /*
             * QML Properties
             */
        public:
            ProjectHandler *project();
            DeclaratorHandler *declarator();
            VariableHandler *variable();
            EnumHandler *enumeration();

            /*
             * Inner c++ properties
             */
        public:
            ProjectHandler &Project();
            DeclaratorHandler &Declarator();
            VariableHandler &Variable();
            EnumHandler &Enumeration();

        private:
            EntityManager m_manager;

        private:
            ProjectHandler m_project;
            DeclaratorHandler m_declarator;
            VariableHandler m_variable;
            EnumHandler m_enumeration;
        };
    }
}

#endif // DNAI_CORE_HANDLERMANAGER_H
