#include "core.h"

#include "client.h"

namespace core
{
    void connect(qint16 serverPort)
    {
        Client::serverPort = serverPort;
        Client::shared();
    }

    namespace declarator
    {
        void declare(EntityID declarator, ENTITY type, const QString &name, VISIBILITY visibility)
        {
            Client::shared().callCommand("DECLARATOR.DECLARE", declarator, type, name, visibility);
        }

        void onDeclared(const std::function<void (EntityID, ENTITY, QString, VISIBILITY, EntityID)> &then)
        {
            Client::shared().registerReply("DECLARATOR.DECLARED", then);
        }

        void onDeclareError(const std::function<void (EntityID, ENTITY, QString, VISIBILITY, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.DECLARE.ERROR", error);
        }

        void remove(EntityID declarator, const QString &name)
        {
            Client::shared().callCommand("DECLARATOR.REMOVE", declarator, name);
        }

        void onRemoved(const std::function<void (EntityID, QString)> &then)
        {
            Client::shared().registerReply("DECLARATOR.REMOVED", then);
        }

        void onRemoveError(const std::function<void (EntityID, QString, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.REMOVE.ERROR", error);
        }

        void rename(EntityID declarator, const QString &name, const QString &newName)
        {
            Client::shared().callCommand("DECLARATOR.RENAME", declarator, name, newName);
        }

        void onRenamed(const std::function<void (EntityID, QString, QString)> &then)
        {
            Client::shared().registerReply("DECLARATOR.RENAMED", then);
        }

        void onRenameError(const std::function<void (EntityID, QString, QString, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.RENAME.ERROR", error);
        }

        void move(EntityID declarator, const QString &name, EntityID newParent)
        {
            Client::shared().callCommand("DECLARATOR.MOVE", declarator, name, newParent);
        }

        void onMoved(const std::function<void (EntityID, QString, EntityID)> &then)
        {
            Client::shared().registerReply("DECLARATOR.MOVED", then);
        }

        void onMoveError(const std::function<void (EntityID, QString, EntityID, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.MOVE.ERROR", error);
        }

        void setVisibility(EntityID declarator, const QString &name, VISIBILITY visibility)
        {
            Client::shared().callCommand("DECLARATOR.SET_VISIBILITY", declarator, name, visibility);
        }

        void onVisibilitySet(const std::function<void (EntityID, QString, VISIBILITY)> &then)
        {
            Client::shared().registerReply("DECLARATOR.VISIBILITY_SET", then);
        }

        void onSetVisibilityError(const std::function<void (EntityID, QString, VISIBILITY, QString)> &error)
        {
            Client::shared().registerReply("DECLARATOR.SET_VISIBILITY.ERROR", error);
        }
    }
}
