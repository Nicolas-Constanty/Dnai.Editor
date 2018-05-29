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
            m_function(m_manager)
        {
            m_project.setup();
            m_declarator.setup();
            m_variable.setup();
            m_enumeration.setup();
            m_function.setup();
        }

        HandlerManager &HandlerManager::Instance()
        {
            //need to instanciate with 'new' because Qt delete the instance
            static HandlerManager *inst = new HandlerManager();

            return *inst;
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
    }
}
