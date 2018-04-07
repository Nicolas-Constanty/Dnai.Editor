#include "dnai/core/projecthandler.h"

namespace dnai
{
    namespace core
    {
        ProjectHandler::ProjectHandler(EntityManager &manager) :
            manager(manager),
            nbproject(0)
        {

        }

        void ProjectHandler::setup()
        {
            //core callbacks
        }

        void ProjectHandler::create(const Project &tocreate)
        {
            //this will trigger entityAdded signal
            manager.addEntity(0, tocreate.getRoot());
            ++nbproject;
        }

        size_t ProjectHandler::getNbProject() const
        {
            return nbproject;
        }
    }
}
