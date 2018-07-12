#include <functional>

#include <QJsonDocument>
#include <QJsonValue>
#include <QStringList>

#include "dnai/core/enumhandler.h"

#include "dnai/commands/commandmanager.h"
#include "dnai/commands/corecommand.h"

#include "dnai/models/gui/declarable/enumtype.h"

#include "dnai/editor.h"

using namespace std::placeholders;

namespace dnai
{
    namespace gcore
    {
        EnumHandler::EnumHandler(EntityManager &manager) :
            manager(manager)
        {}

        void EnumHandler::setup()
        {
            QObject::connect(&manager,  SIGNAL(entityAdded(::core::EntityID,models::Entity&)),
                             this,      SLOT(onEntityAdded(::core::EntityID,models::Entity&)));

            ::core::enumeration::onValueSet(std::bind(&EnumHandler::onValueSet, this, _1, _2, _3));
            ::core::enumeration::onSetValueError(std::bind(&EnumHandler::onSetValueError, this, _1, _2, _3, _4));
            ::core::enumeration::onValueRemoved(std::bind(&EnumHandler::onValueRemoved, this, _1, _2));
            ::core::enumeration::onRemoveValueError(std::bind(&EnumHandler::onRemoveValueError, this, _1, _2, _3));
        }

        void EnumHandler::onEntityAdded(::core::EntityID id, models::Entity &entity)
        {
            models::gui::declarable::EnumType *enumtype = entity.guiModel<models::gui::declarable::EnumType>();

            //if entity is an enum
            if (enumtype != nullptr)
            {
                //replicate its values on core
                for (QString const &name : enumtype->values())
                {
                    setValue(id, name, enumtype->getValue(name), false);
                }
            }
        }

        void EnumHandler::renameValue(quint32 entity, QString name, QString newName, bool save)
        {
            models::Entity &enu = manager.getEntity(entity);
            QString value = enu.guiModel<models::EnumType>()->getValue(name);

            qDebug() << "==Core== Enum.RenameValue(" << entity << ", " << name << ", " << newName << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(new commands::CoreCommand("Enumeration.Rename", save,
                [this, &enu, name, newName, value](){
                    m_pendingRemove.push(name);
                    core::enumeration::setValue(enu.id(), newName, value);
                },
                [this, &enu, name, newName, value]() {
                    m_pendingRemove.push(newName);
                    core::enumeration::setValue(enu.id(), name, value);
                }
            ));
        }

        void EnumHandler::setValue(quint32 entity, QString name, QString value, bool save)
        {
            models::Entity &enu = manager.getEntity(entity);

            if (name.isEmpty())
            {
                name = enu.name() + "(" + QString::number(qrand()) + ")";
            }

            qDebug() << "==Core== Enum.SetValue(" << entity << ", " << name << ", " << value << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", save,
                    [&enu, name, value]() {
                        core::enumeration::setValue(enu.id(), name, value);
                    },
                    [&enu, name]() {
                        core::enumeration::removeValue(enu.id(), name);
                    }
                )
            );
        }

        void EnumHandler::removeValue(quint32 entity, QString const &name, bool save)
        {
            models::Entity &enu = manager.getEntity(entity);
            const QString value = enu.guiModel<models::gui::declarable::EnumType>()->getValue(name);

            qDebug() << "==Core== Enum.RemoveValue(" << entity << ", " << name << ") => save(" << save << ")";

            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", save,
                    [&enu, name] () {
                        core::enumeration::removeValue(enu.id(), name);
                    },
                    [&enu, name, value]() {
                        core::enumeration::setValue(enu.id(), name, value);
                    }
                )
            );
        }

        void EnumHandler::onValueSet(::core::EntityID enumeration, const QString &name, QString const &value)
        {
            models::Entity &enu = manager.getEntity(enumeration);
            models::gui::declarable::EnumType *data = enu.guiModel<models::gui::declarable::EnumType>();

            data->addEntry(name, value);

            qDebug() << "==Core== Enum.ValueSet(" << enumeration << ", " << name << ", " << value << ")";

            //when an enum value is renamed, don't make a success until the old one is removed
            if (!m_pendingRemove.empty())
            {
                core::enumeration::removeValue(enumeration, m_pendingRemove.front());
                m_pendingRemove.pop();
            }
            else
            {
                commands::CoreCommand::Success();
            }

            emit valueSet(&enu, name, value);
        }

        void EnumHandler::onSetValueError(::core::EntityID, const QString &name, QString const &value, const QString &message)
        {
            commands::CoreCommand::Error();
            dnai::Editor::instance().notifyError("Cannot set \"" + name + "\" to value \"" + value + "\" to enumeration: " + message);
        }

        void EnumHandler::onValueRemoved(::core::EntityID enumeration, const QString &name)
        {
            models::Entity &enu = manager.getEntity(enumeration);
            models::gui::declarable::EnumType *data = enu.guiModel<models::gui::declarable::EnumType>();

            data->deleteEntry(name);
            commands::CoreCommand::Success();
            emit valueRemoved(&enu, name);
            qDebug() << "==Core== Enum.ValueRemoved(" << enumeration << ", " << name << ")";
        }

        void EnumHandler::onRemoveValueError(::core::EntityID, const QString &name, const QString &message)
        {
            commands::CoreCommand::Error();
            dnai::Editor::instance().notifyError("Cannot remove value \"" + name + "\" from enumeration: " + message);
        }
    }
}
