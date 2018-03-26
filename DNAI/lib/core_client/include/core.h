#ifndef CORE_CLIENT_CORE_H
#define CORE_CLIENT_CORE_H

#include <functional>
#include <cinttypes>

#include <QString>

namespace core
{
    using EntityID = uint32_t;

    enum ENTITY
    {
        CONTEXT = 0,
        VARIABLE = 1,
        FUNCTION = 2,
        DATA_TYPE = 3,
        ENUM_TYPE = 4,
        OBJECT_TYPE = 5,
        LIST_TYPE = 6
    };

    enum VISIBILITY
    {
        PRIVATE = 0,
        PUBLIC = 1
    };

    enum INSTRUCTION
    {

    };

    void connect(qint16 serverPort);

    namespace declarator
    {
        void declare(EntityID declarator, ENTITY type, QString const &name, VISIBILITY visibility);
        void onDeclared(std::function<void(EntityID, ENTITY, QString, VISIBILITY, EntityID)> const &then);
        void onDeclareError(std::function<void(EntityID, ENTITY, QString, VISIBILITY, QString)> const &error);

        void remove(EntityID declarator, QString const &name);
        void onRemoved(std::function<void(EntityID, QString)> const &then);
        void onRemoveError(std::function<void(EntityID, QString, QString)> const &error);

        void rename(EntityID declarator, QString const &name, QString const &newName);
        void onRenamed(std::function<void(EntityID, QString, QString)> const &then);
        void onRenameError(std::function<void(EntityID, QString, QString, QString)> const &error);

        void move(EntityID declarator, QString const &name, EntityID newParent);
        void onMoved(std::function<void(EntityID, QString, EntityID)> const &then);
        void onMoveError(std::function<void(EntityID, QString, EntityID, QString)> const &error);

        void setVisibility(EntityID declarator, QString const &name, VISIBILITY visibility);
        void onVisibilitySet(std::function<void(EntityID, QString, VISIBILITY)> const &then);
        void onSetVisibilityError(std::function<void(EntityID, QString, VISIBILITY, QString)> const &error);
    }
}

#endif // CORE_CLIENT_CORE_H
