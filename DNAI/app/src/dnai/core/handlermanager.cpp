#include "dnai/core/handlermanager.h"

namespace dnai
{
    namespace core
    {
        HandlerManager::HandlerManager() :
            m_manager(),
            m_project(m_manager),
            m_declarator(m_manager)
        {
            m_project.setup();
            m_declarator.setup();
        }

        HandlerManager &HandlerManager::Instance()
        {
            static HandlerManager inst;

            return inst;
        }

        ProjectHandler &HandlerManager::Project()
        {
            return m_project;
        }

        DeclaratorHandler &HandlerManager::Declarator()
        {
            return m_declarator;
        }
    }
}
