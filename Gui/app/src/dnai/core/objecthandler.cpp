#include <functional>

#include "dnai/core/objecthandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        ObjectHandler::ObjectHandler(EntityManager &manager) :
            manager(manager)
        {

        }

        void ObjectHandler::setup()
        {
            core::object::onAttributeAdded(std::bind(&ObjectHandler::onAttributeAdded, this, _1, _2, _3, _4));
            core::object::onAddAttributeError(std::bind(&ObjectHandler::onAddAttributeError, this, _1, _2, _3, _4, _5));
        }

        void ObjectHandler::addAttribute(quint32 obj, QString name, quint32 typ, qint32 visi, bool save)
        {
            qDebug() << "==Core== Class.AddAttribute(" << obj << ", " << name << ", " << typ << ", " << visi << ") => save(" << save << ")";

            models::Entity &object = manager.getEntity(obj);
            models::Entity &type = manager.getEntity(typ);

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Class.AddAttribute", save,
                [&object, &type, name, visi]() {
                    core::object::addAttribute(object.id(), name, type.id(), static_cast<VISIBILITY>(visi));
                },
                [&object, name]() {
                    core::object::removeAttribute(object.id(), name);
                }
            ));
        }

        void ObjectHandler::onAttributeAdded(EntityID obj, QString name, EntityID typ, VISIBILITY visi)
        {
            models::Entity &object = manager.getEntity(obj);
            models::ObjectType *data = object.guiModel<models::ObjectType>();
            models::Entity &type = manager.getEntity(typ);

            qDebug() << "==Core== Class.AttributeAdded(" << obj << ", " << name << ", " << typ << ", " << visi << ")";
            data->addAttribute(name, type.id());
            commands::CoreCommand::Success();
            emit attributeAdded(&object, name, &type, visi);
        }

        void ObjectHandler::onAddAttributeError(EntityID obj, QString name, EntityID type, VISIBILITY visi, QString msg)
        {
            Q_UNUSED(obj)
            Q_UNUSED(type)
            Q_UNUSED(visi)

            commands::CoreCommand::Error();
            Editor::instance().notifyError("Unable to add attribute " + name + ": " + msg);
        }
    }
}
