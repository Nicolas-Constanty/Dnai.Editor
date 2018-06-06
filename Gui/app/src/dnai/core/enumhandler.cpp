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
        {

        }

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
                int val = 0;
                //replicate its values on core
                for (auto nam : enumtype->values())
                {
                    setValue(id, nam, val, false);
                }
            }
        }

        void EnumHandler::setValue(quint32 entity, QString name, QJsonValue const &value, bool save)
        {
            if (name.isEmpty())
            {
                name = QString("Empty ") + QString::number(qrand());
            }

            qDebug() << "==Core== Enum.SetValue(" << entity << ", " << name << ", " << value << ") => save(" << save << ")";
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", save,
                    std::bind(&::core::enumeration::setValue, entity, name, value.toString()),
                    std::bind(&::core::enumeration::removeValue, entity, name)
                )
            );
        }

        void EnumHandler::removeValue(quint32 entity, QString const &name, bool save)
        {
            const int value = manager.getEntity(entity).guiModel<models::gui::declarable::EnumType>()->values().indexOf(name);

            qDebug() << "==Core== Enum.RemoveValue(" << entity << ", " << name << ") => save(" << save << ")";
            commands::CommandManager::Instance()->exec(
                new commands::CoreCommand("Enum.SetValue", save,
                    std::bind(&::core::enumeration::removeValue, entity, name),
                    std::bind(&::core::enumeration::setValue, entity, name, QString::number(value))
                )
            );
        }

        void EnumHandler::onValueSet(::core::EntityID enumeration, const QString &name, QString const &value)
        {
            QJsonValue val = QJsonDocument::fromJson(value.toUtf8()).toVariant().toJsonValue();
            models::gui::declarable::EnumType *data = manager.getEntity(enumeration).guiModel<models::gui::declarable::EnumType>();

            data->addEntry(name);
            commands::CoreCommand::Success();
            emit valueSet(data, name, val);
            qDebug() << "==Core== Enum.ValueSet(" << enumeration << ", " << name << ", " << value << ")";
        }

        void EnumHandler::onSetValueError(::core::EntityID, const QString &name, QString const &value, const QString &message)
        {
            commands::CoreCommand::Error();
            dnai::Editor::instance().notifyError("Cannot set \"" + name + "\" to value \"" + value + "\" to enumeration: " + message);
        }

        void EnumHandler::onValueRemoved(::core::EntityID enumeration, const QString &name)
        {
            models::gui::declarable::EnumType *data = manager.getEntity(enumeration).guiModel<models::gui::declarable::EnumType>();

            data->deleteEntry(name);
            commands::CoreCommand::Success();
            emit valueRemoved(data, name);
            qDebug() << "==Core== Enum.ValueRemoved(" << enumeration << ", " << name << ")";
        }

        void EnumHandler::onRemoveValueError(::core::EntityID, const QString &name, const QString &message)
        {
            commands::CoreCommand::Error();
            dnai::Editor::instance().notifyError("Cannot remove value \"" + name + "\" from enumeration: " + message);
        }
    }
}
