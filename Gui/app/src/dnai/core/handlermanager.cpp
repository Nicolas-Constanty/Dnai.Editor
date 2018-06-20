#include "dnai/core/handlermanager.h"

namespace dnai
{
    namespace gcore
    {
        HandlerManager::HandlerManager() :
            m_manager(),
            m_project(m_manager),
            m_declarator(m_manager),
            m_variable(m_manager),
            m_enumeration(m_manager),
            m_function(m_manager),
            m_global(),
            m_object(m_manager),
            m_list(m_manager)
        {

        }

        HandlerManager &HandlerManager::Instance()
        {
            //need to instanciate with 'new' because Qt delete the instance
            static HandlerManager *inst = nullptr;

            if (inst == nullptr)
            {
                inst = new HandlerManager();
                inst->setup();
            }
            return *inst;
        }

        void HandlerManager::setup()
        {
            QObject::connect(&m_manager,    SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,          SLOT(onEntityAdded(::core::EntityID,models::Entity&)));
            QObject::connect(&m_manager,    SIGNAL(entityRemoved(::core::EntityID,models::Entity&)),
                             this,          SLOT(onEntityRemoved(::core::EntityID,models::Entity&)));

            m_manager.setup();
            m_project.setup();
            m_declarator.setup();
            m_variable.setup();
            m_enumeration.setup();
            m_function.setup();
            m_global.setup();
            m_object.setup();
            m_list.setup();
        }

        ProjectHandler *HandlerManager::project()
        {
            return &m_project;
        }

        DeclaratorHandler *HandlerManager::declarator()
        {
            return &m_declarator;
        }

        VariableHandler *HandlerManager::variable()
        {
            return &m_variable;
        }

        EnumHandler *HandlerManager::enumeration()
        {
            return &m_enumeration;
        }

        FunctionHandler *HandlerManager::function()
        {
            return &m_function;
        }

        GlobalHandler *HandlerManager::global()
        {
            return &m_global;
        }

        ObjectHandler *HandlerManager::getClass()
        {
            return &m_object;
        }

        ListHandler *HandlerManager::List()
        {
            return &m_list;
        }

        ProjectHandler &HandlerManager::Project()
        {
            return m_project;
        }

        DeclaratorHandler &HandlerManager::Declarator()
        {
            return m_declarator;
        }

        VariableHandler &HandlerManager::Variable()
        {
            return m_variable;
        }

        EnumHandler &HandlerManager::Enumeration()
        {
            return m_enumeration;
        }

        FunctionHandler &HandlerManager::Function()
        {
            return m_function;
        }

        GlobalHandler &HandlerManager::Global()
        {
            return m_global;
        }

        ObjectHandler &HandlerManager::Class()
        {
            return m_object;
        }

        QList<QVariant> HandlerManager::types()
        {
            QList<QVariant> toret;

            for (models::Entity *curr : m_types)
            {
                toret.append(QVariant::fromValue(curr));
            }
            return toret;
        }

        models::Entity *HandlerManager::getType(int index)
        {
            return m_types[index];
        }

        int HandlerManager::getTypeIndex(QUuid typeuid)
        {
            return m_types.indexOf(getEntity(typeuid));
        }

        models::Entity *HandlerManager::getEntity(QUuid guid)
        {
            return m_manager.getEntity(guid);
        }

        models::Entity *HandlerManager::getEntity(quint32 id)
        {
            if (m_manager.contains(id))
                return &m_manager.getEntity(id);
            return nullptr;
        }

        void HandlerManager::onEntityAdded(EntityID id, models::Entity &entity)
        {
            Q_UNUSED(id)

            ENTITY type = static_cast<ENTITY>(entity.entityType());

            if (type == ENTITY::DATA_TYPE || type == ENTITY::ENUM_TYPE
                || type == ENTITY::LIST_TYPE || type == ENTITY::OBJECT_TYPE)
            {
                m_types.append(&entity);
                emit typesChanged(types());
            }
        }

        void HandlerManager::onEntityRemoved(EntityID id, models::Entity &entity)
        {
            Q_UNUSED(id)

            ENTITY type = static_cast<ENTITY>(entity.entityType());

            if (type == ENTITY::DATA_TYPE || type == ENTITY::ENUM_TYPE
                || type == ENTITY::LIST_TYPE || type == ENTITY::OBJECT_TYPE)
            {
                m_types.removeOne(&entity);
                emit typesChanged(types());
            }
        }
    }
}
