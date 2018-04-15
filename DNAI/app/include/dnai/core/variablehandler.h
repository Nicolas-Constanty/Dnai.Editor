#ifndef DNAI_CORE_VARIABLEHANDLER_H
#define DNAI_CORE_VARIABLEHANDLER_H

#include <QObject>

#include "entitymanager.h"
#include "dnai/enums/core/coreenums.h"

namespace dnai
{
    namespace core
    {
        class VariableHandler : public QObject
        {
            Q_OBJECT

        public:
            VariableHandler(EntityManager &manager);
            virtual ~VariableHandler() = default;

        public:
            void setup();

        public slots:
            void onEntityAdded(enums::core::EntityID id, models::Entity &entity);

        public:
            void setType(models::Entity const &variable, models::Entity const &type);
            void setValue(models::Entity const &variable, QJsonObject const &value);

        private:
            models::gui::declarable::Variable *getVariableData(enums::core::EntityID variable, bool throws = false);

        private:
            void onTypeSet(enums::core::EntityID variable, enums::core::EntityID type);
            void onSetTypeError(enums::core::EntityID variable, enums::core::EntityID type, QString const &message);

            void onValueSet(enums::core::EntityID variable, QString const &value);
            void onSetValueError(enums::core::EntityID variable, QString const &value, QString const &message);

        private:
            EntityManager &manager;
        };
    }
}

#endif // DNAI_CORE_VARIABLEHANDLER_H
