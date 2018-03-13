#ifndef DNAI_MODELS_ENTITY_H
#define DNAI_MODELS_ENTITY_H

#include "dnai/models/core/entity.h"
#include "dnai/models/gui/declarable/entity.h"
#include "dnai/enums/core/core.h"
#include "dnai/interfaces/imodel.h"

namespace dnai
{
    namespace models
    {
        class Entity : public interfaces::IModel<Entity>
        {
            Q_OBJECT
            Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
            Q_PROPERTY(qint32 containerId READ containerId WRITE setContainerId NOTIFY containerIdChanged)
            Q_PROPERTY(dnai::enums::core::ENTITY entityType READ entityType WRITE setEntityType NOTIFY entityTypeChanged)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(dnai::enums::core::VISIBILITY visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged)
            Q_PROPERTY(int index READ id WRITE setIndex NOTIFY indexChanged)
            Q_PROPERTY(int listIndex READ listIndex WRITE setListIndex NOTIFY listIndexChanged)
            Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
            Q_PROPERTY(core::Entity *coreModel READ coreModel WRITE setCoreModel NOTIFY coreModelChanged)
                    //			Q_PROPERTY(EntityGUI *guiModel READ guiModel CONSTANT)
        public:
            explicit Entity();
            explicit Entity(core::Entity *coremodel, interfaces::IEntity *guimodel = nullptr, GenericTreeItem *parent = nullptr);
            explicit Entity(core::Entity *coremodel, GenericTreeItem *parent = nullptr, interfaces::IEntity *guimodel = nullptr);

            virtual ~Entity() = default;
        public:
            qint32 id() const;
            qint32 containerId() const;
            enums::core::ENTITY entityType() const;
            const QString &name() const;
            enums::core::VISIBILITY visibility() const;
            int index() const;
            int listIndex() const;
            const QString& description() const;
            virtual core::Entity *coreModel() const;
            virtual interfaces::IEntity *guiModel() const;

        public:
            void setId(qint32 id);
            void setContainerId(qint32 containerId) const;
            void setEntityType(enums::core::ENTITY type) const;
            void setName(const QString &) const;
            void setVisibility(enums::core::VISIBILITY) const;
            void setIndex(int index);
            void setListIndex(int listIndex);
            void setDescription(const QString& description);
            virtual void setCoreModel(core::Entity *model);

        signals:
            void idChanged(qint32 id);
            void containerIdChanged(qint32 containerId) const;
            void entityTypeChanged(enums::core::ENTITY type) const;
            void nameChanged(const QString &) const;
            void visibilityChanged(enums::core::VISIBILITY) const;
            void indexChanged(int index) const;
            void listIndexChanged(int listIndex) const;
            void descriptionChanged(const QString& description) const;
            void coreModelChanged(core::Entity *model);

        //Implementation of ISerializable
        public:
            void serialize(QJsonObject& obj) const override;
            void _deserialize(const QJsonObject& obj) override;
            int columnCount() const override;
        private:
            core::Entity *m_dataCore;
            interfaces::IEntity *m_dataGUI;
        };
    }
}

#endif // DNAI_MODELS_ENTITY_H
