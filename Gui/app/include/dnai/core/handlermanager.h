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
#include "globalhandler.h"

namespace dnai
{
    namespace gcore
    {
        class HandlerManager : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(ProjectHandler *project READ project CONSTANT)
            Q_PROPERTY(DeclaratorHandler *declarator READ declarator CONSTANT)
            Q_PROPERTY(VariableHandler *variable READ variable CONSTANT)
            Q_PROPERTY(EnumHandler *enumeration READ enumeration CONSTANT)
            Q_PROPERTY(FunctionHandler *Function READ function CONSTANT)
            Q_PROPERTY(GlobalHandler *global READ global CONSTANT)

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
            FunctionHandler *function();
            GlobalHandler *global();

            /*
             * Inner c++ properties
             */
        public:
            ProjectHandler &Project();
            DeclaratorHandler &Declarator();
            VariableHandler &Variable();
            EnumHandler &Enumeration();
            FunctionHandler &Function();
            GlobalHandler &Global();

        private:
            EntityManager m_manager;

        private:
            ProjectHandler m_project;
            DeclaratorHandler m_declarator;
            VariableHandler m_variable;
            EnumHandler m_enumeration;
            FunctionHandler m_function;
            GlobalHandler m_global;
        };
    }
}

#endif // DNAI_CORE_HANDLERMANAGER_H
