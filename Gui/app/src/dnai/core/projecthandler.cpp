#include <functional>

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/core/projecthandler.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        ProjectHandler::ProjectHandler(EntityManager &manager) :
            manager(manager)
        {}

        void ProjectHandler::setup()
        {
            ::core::global::onProjectCreated(std::bind(&ProjectHandler::onCreated, this, _1, _2));
            ::core::global::onCreateProjectError(std::bind(&ProjectHandler::onCreateError, this, _1, _2));
        }

        void ProjectHandler::create(Project *tocreate, bool save)
        {
            qDebug() << "==Core== Project.Create(" << tocreate->name() << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(new commands::CoreCommand(
                "Project.Create", save,
                [this, tocreate](){
                    pendingProjects.push(tocreate);
                    ::core::global::createProject(tocreate->name());
                },
                [](){} //do remove project
            ));
        }

        void ProjectHandler::onCreated(const QString &name, ::core::EntityID rootEntity)
        {
            if (pendingProjects.empty() || pendingProjects.front()->name() != name)
            {
                Editor::instance().notifyWarning("Someone tried to declare a project");
                return;
            }

            commands::CoreCommand::Success();

            Project *curr = pendingProjects.front();

            manager.addEntity(rootEntity, curr->getRoot());

            pendingProjects.pop();
            qDebug() << "==Core== Project.Created(" << name << ", " << rootEntity << ")";
        }

        void ProjectHandler::onCreateError(const QString &name, const QString &error)
        {
            if (pendingProjects.empty() || pendingProjects.front()->name() != name)
            {
                Editor::instance().notifyWarning("Someone failed to declare a project");
                return;
            }

            commands::CoreCommand::Error();

            Editor::instance().notifyError("Failed to create project: " + error);
        }
    }
}
