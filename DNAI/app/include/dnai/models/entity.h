#ifndef DNAI_MODELS_ENTITY_H
#define DNAI_MODELS_ENTITY_H

#include "dnai/models/core/entity.h"
#include "dnai/models/gui/declarable/entity.h"
#include "dnai/enums/core/coreenums.h"
#include "dnai/interfaces/imodel.h"
#include "gui/data/entitycolum.h"
#include "gui/declarable/variable.h"
#include "gui/declarable/context.h"
#include "dnai/models/property.h"

namespace dnai
{
    namespace models
    {
        class Entity;
        class Column : public QAbstractListModel, public interfaces::ASerializable<Column>
        {
            Q_OBJECT
			Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
			Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
			Q_PROPERTY(dnai::models::Entity *parentRef READ parentRef CONSTANT)
			Q_PROPERTY(QString listIndex READ listIndex WRITE setListIndex NOTIFY listIndexChanged)

			enum ROLES
			{
				ENTITIES = Qt::UserRole + 1,
			};
        public:
            explicit Column(QObject *parent = nullptr) : QAbstractListModel(parent) {}
            explicit Column(Entity *pr, QObject *parent = nullptr);
            virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role) const override;
	        void append(Entity* e, const QModelIndex& parent = QModelIndex());
	        void remove(Entity* e, const QModelIndex& parent = QModelIndex());
			const QString &name() const;
			const QString &description() const;
			void setName(const QString &name);
			void setDescription(const QString& description);
			QString listIndex() const;
			void setListIndex(const QString &s);
			Entity *parentRef() const;

		signals:
			void descriptionChanged(const QString &desc);
			void nameChanged(const QString &desc);
			void listIndexChanged(const QString list);
        private:
			virtual QHash<int, QByteArray> roleNames() const override;
        public:
	        void serialize(QJsonObject& obj) const override;
        protected:
	        void _deserialize(const QJsonObject& obj) override;
        public:
	        const gui::data::EntityColumn& datas() const;
	        bool setDatas(const gui::data::EntityColumn& data);

        public:
            const QList<Entity *> &getEntities() const;

        private:
            Entity *m_target;
            QList<Entity *> m_entities;
	        gui::data::EntityColumn m_data;
            Entity *m_parent;
        };

        class Entity : public interfaces::IModel<Entity>
        {
            Q_OBJECT
            Q_PROPERTY(qint32 id READ id WRITE setId NOTIFY idChanged)
            Q_PROPERTY(qint32 containerId READ containerId WRITE setContainerId NOTIFY containerIdChanged)
            Q_PROPERTY(qint32 entityType READ entityType WRITE setEntityType NOTIFY entityTypeChanged)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
			Q_PROPERTY(bool isRoot READ isRoot WRITE setIsRoot NOTIFY isRootChanged)
            Q_PROPERTY(dnai::enums::core::VISIBILITY visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged)
            Q_PROPERTY(int index READ id WRITE setIndex NOTIFY indexChanged)
            Q_PROPERTY(QString listIndex READ listIndex WRITE setListIndex NOTIFY listIndexChanged)
            Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
            Q_PROPERTY(core::Entity *coreModel READ coreModel WRITE setCoreModel NOTIFY coreModelChanged)
			Q_PROPERTY(bool expanded READ expanded WRITE setExpanded NOTIFY expandedChanged)
			Q_PROPERTY(dnai::models::Entity *parentRef READ parentRef CONSTANT)
			Q_PROPERTY(dnai::models::Property *editableProperty READ editableProperty WRITE setEditableProperty NOTIFY editablePropertyChanged)
                    //			Q_PROPERTY(EntityGUI *guiModel READ guiModel CONSTANT)

        public:
            explicit Entity();
            explicit Entity(core::Entity *coremodel, Entity *parent = nullptr, interfaces::IEntity *guimodel = nullptr);

            virtual ~Entity();
        public:
			bool isRoot() const;
            qint32 id() const;
            qint32 containerId() const;
            int entityType() const;
            const QString &name() const;
            const QString fullName() const;
            const QString childFullName(QString const &childName) const;
            enums::core::VISIBILITY visibility() const;
            int index() const;
			QString listIndex() const;
            const QString &description() const;
            virtual core::Entity *coreModel() const;
            virtual interfaces::IEntity *guiModel() const;
			template<class T>
			T *guiModel() const;
            bool expanded() const;
			Entity *parentRef() const;
			const QMap<QUuid, Column *> &columns();
			Property *editableProperty() const;

        public:
			void setIsRoot(bool isRoot);
            void setId(qint32 id);
            void setContainerId(qint32 containerId) const;
            void setEntityType(qint32 type) const;
            void setName(const QString &) const;
            void setVisibility(enums::core::VISIBILITY) const;
            void setIndex(int index);
            void setListIndex(const QString &listIndex);
            void setDescription(const QString& description);
            virtual void setCoreModel(core::Entity *model);
			void setExpanded(bool exp);
			void setEditableProperty(Property *p);
			virtual void appendChild(Entity* child) override;

        signals:
			void isRootChanged(bool isroot);
            void idChanged(qint32 id);
            void containerIdChanged(qint32 containerId) const;
            void entityTypeChanged(qint32 type) const;
            void nameChanged(const QString &) const;
            void visibilityChanged(enums::core::VISIBILITY) const;
            void indexChanged(int index) const;
            void listIndexChanged(const QString &listIndex) const;
            void descriptionChanged(const QString& description) const;
            void coreModelChanged(core::Entity *model);
			void entityChildrenChanged(models::Entity *e);
			void expandedChanged(bool exp);
			void editablePropertyChanged(Property *p);

        //Implementation of ISerializable
        public:
            void serialize(QJsonObject& obj) const override;
            void _deserialize(const QJsonObject& obj) override;
	        int columnCount() const override;
			Q_INVOKABLE QVariant listColumn() const;
			Q_INVOKABLE int row() const override;
			Q_INVOKABLE void setProp(int row, const QVariant &value);

        private:
            core::Entity *m_dataCore;
            interfaces::IEntity *m_dataGUI;
			bool m_isRoot = false;
			QVariant m_entityChildren;
			QMap<QUuid, Column *> m_columns;
			QList<QObject *> m_columslist;
			Property *m_editableProperty;
        };

		using Context = dnai::models::gui::declarable::Context;
		using EnumType = dnai::models::gui::declarable::EnumType;
		using Function = dnai::models::gui::declarable::Function;
		using ListType = dnai::models::gui::declarable::ListType;
		using ObjectType = dnai::models::gui::declarable::ObjectType;
		using Variable = dnai::models::gui::declarable::Variable;

	    template <class T>
	    T* Entity::guiModel() const
	    {
			return dynamic_cast<T *>(guiModel());
	    }
    }
}

#endif // DNAI_MODELS_ENTITY_H
