#include <functional>

#include "core.h"

#include "dnai/core/globalhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        void GlobalHandler::setup()
        {
            core::global::onSaved(std::bind(&GlobalHandler::onSaved, this, _1));
            core::global::onSaveError(std::bind(&GlobalHandler::onSaveError, this, _1, _2));

            core::global::onLoaded(std::bind(&GlobalHandler::onLoaded, this, _1));
            core::global::onLoadError(std::bind(&GlobalHandler::onLoadError, this, _1, _2));
        }

        void GlobalHandler::save(const QString &path)
        {
            qDebug() << "==Core== Global.Save(" << path << ") => save( false )";
            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Global.Save", false,
                std::bind(&core::global::save, path),
                nullptr
            ));
        }

        void GlobalHandler::load(const QString &path)
        {
            qDebug() << "==Core== Global.Load(" << path << ") => save( false )";
            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Global.Load", false,
                std::bind(&core::global::load, path),
                nullptr
            ));
        }

        void GlobalHandler::onSaved(const QString &path)
        {
            qDebug() << "==Core== Global.Saved(" << path << ")";
            emit saved(path);
        }

        void GlobalHandler::onSaveError(const QString &path, const QString &msg)
        {
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to build solution at path \"" + path + "\": " + msg);
            emit saveError(path, msg);
        }

        void GlobalHandler::onLoaded(const QString &path)
        {
            qDebug() << "==Core== Global.Loaded(" << path << ")";
            emit loaded(path);
        }

        void GlobalHandler::onLoadError(const QString &path, const QString &msg)
        {
            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to load solution from \"" + path + "\": " + msg);
            emit loadError(path, msg);
        }
    }
}
