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
            m_object(m_manager)
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
            m_project.setup();
            m_declarator.setup();
            m_variable.setup();
            m_enumeration.setup();
            m_function.setup();
            m_global.setup();
            m_object.setup();
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
    }
}
