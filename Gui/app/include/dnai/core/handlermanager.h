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
#include "resourcehandler.h"

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
            Q_PROPERTY(ObjectHandler *Class READ getClass CONSTANT)
            Q_PROPERTY(ListHandler *List READ List CONSTANT)
            Q_PROPERTY(ResourceHandler *Resource READ Resource CONSTANT)

            Q_PROPERTY(QList<QVariant> types READ types NOTIFY typesChanged)

        private:
            HandlerManager();

        public:
            static HandlerManager &Instance();

        public:
            void setup();

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
            ObjectHandler *getClass();
            ListHandler *List();
            ResourceHandler *Resource();

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
            ObjectHandler &Class();

        public:
            QList<QVariant> types();
            Q_INVOKABLE dnai::models::Entity *getType(int index);
            Q_INVOKABLE int getTypeIndex(QUuid typeuid);

        public:
            dnai::models::Entity *getEntity(QUuid guid);
            Q_INVOKABLE dnai::models::Entity *getEntityGui(QUuid guid);
            Q_INVOKABLE dnai::models::Entity *getEntity(quint32 id);
            Q_INVOKABLE dnai::models::Entity *getEntityByFullName(const QString &name);

        public slots:
            void onEntityAdded(::core::EntityID id, models::Entity &entity);
            void onEntityRemoved(::core::EntityID id, models::Entity &entity);

        signals:
            void typesChanged(QList<QVariant> types);

        private:
            EntityManager m_manager;

        private:
            ProjectHandler m_project;
            DeclaratorHandler m_declarator;
            VariableHandler m_variable;
            EnumHandler m_enumeration;
            FunctionHandler m_function;
            GlobalHandler m_global;
            ObjectHandler m_object;
            ListHandler m_list;
            ResourceHandler m_resource;

        private:
            QList<models::Entity *>    m_types;
        };
    }
}

#endif // DNAI_CORE_HANDLERMANAGER_H
