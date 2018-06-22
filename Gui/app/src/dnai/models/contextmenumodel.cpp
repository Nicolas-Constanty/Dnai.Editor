#include <QJsonDocument>

#include "dnai/models/contextMenuModel.h"
#include "dnai/models/entity.h"
#include "dnai/enums/core/instructionid.h"

#include "dnai/core/handlermanager.h"

namespace dnai
{
	namespace models
    {
        ContextMenuItem::ContextMenuItem(ContextMenuItem *parent) :
            GenericTreeItem<ContextMenuItem>::GenericTreeItem(parent)
        {

        }

        const QString& ContextMenuItem::name() const
		{
			return m_name;
		}

		const QString& ContextMenuItem::description() const
		{
			return m_descrition;
		}

		int ContextMenuItem::inputs() const
		{
			return m_inputs;
		}

		int ContextMenuItem::outputs() const
		{
			return m_outputs;
		}

		int ContextMenuItem::instructionId() const
		{
			return m_instructionId;
		}

		const QString& ContextMenuItem::nodeName() const
		{
			return m_nodeName;
		}

		void ContextMenuItem::setNodeName(const QString& name)
		{
			if (name == m_nodeName)
				return;
			m_nodeName = name;
            emit nodeNameChanged(name);
        }

        void ContextMenuItem::setType(const int t)
        {
            if (t == m_type)
                return;
            m_type = t;
            emit typeChanged(t);
        }

        void ContextMenuItem::setConstruction(const QList<qint32> &value)
        {
            if (m_construction == value)
                return;
            m_construction = value;
            emit constructionChanged(m_construction);
        }

		void ContextMenuItem::setName(const QString& name)
		{
			if (name == m_name)
				return;
			m_name = name;
			emit nameChanged(name);
		}

		void ContextMenuItem::setDescription(const QString& descr)
		{
			if (descr == m_descrition)
				return;
			m_descrition = descr;
			emit descriptionChanged(descr);
		}

		void ContextMenuItem::setInputs(int i)
		{
			if (i == m_inputs)
				return;
			m_inputs = i;
			emit inputsChanged(i);
		}

		void ContextMenuItem::setOutputs(int o)
		{
			if (o == m_outputs)
				return;
			m_outputs = o;
			emit outputsChanged(o);
		}

		void ContextMenuItem::setInstructionId(int instr)
		{
			if (instr == m_instructionId)
				return;
			m_instructionId = instr;
			emit instructionIdChanged(instr);
		}

		int ContextMenuItem::columnCount() const
		{
            return 1;
        }

        int ContextMenuItem::type() const
        {
            return m_type;
        }

        const QList<qint32> &ContextMenuItem::construction() const
        {
            return m_construction;
        }

		int ContextMenuItem::flowIn() const
		{
			return m_flowIn;
		}

		int ContextMenuItem::flowOut() const
		{
			return m_flowOut;
		}

		const QStringList& ContextMenuItem::inputNames() const
		{
			return m_inputNames;
		}

		const QStringList& ContextMenuItem::outputNames() const
		{
			return m_outputNames;
		}

		void ContextMenuItem::appendInputName(const QString& name)
		{
			m_inputNames.append(name);
			emit inputNamesChanged(m_inputNames);
		}

		void ContextMenuItem::appendOutputName(const QString& name)
		{
			m_outputNames.append(name);
            emit outputNamesChanged(m_outputNames);
        }

        QString ContextMenuItem::fullPath() const
        {
            return (parentItem() != nullptr ? parentItem()->fullPath() : "") + "/" + name();
        }

		void ContextMenuItem::setInputNames(const QStringList& value)
		{
			if (m_inputNames == value)
				return;
			m_inputNames = value;
			emit inputNamesChanged(value);
		}

		void ContextMenuItem::setOutputNames(const QStringList& value)
		{
			if (m_outputNames == value)
				return;
			m_outputNames = value;
			emit outputNamesChanged(value);
		}

		void ContextMenuItem::setFlowIn(const int value)
		{
			if (m_flowIn == value)
				return;
			m_flowIn = value;
			emit flowInChanged(value);
		}

		void ContextMenuItem::setFlowOut(const int value)
		{
			if (m_flowOut == value)
				return;
			m_flowOut = value;
			emit flowOutChanged(value);
		}

		ContextMenuModel::ContextMenuModel(QObject* parent)
			: QAbstractItemModel(parent), m_root(nullptr), m_variableGetter(nullptr), m_variableSetter(nullptr),
			  m_returns(nullptr), m_parameters(nullptr)
		{
		}

		ContextMenuModel::ContextMenuModel(const QJsonObject &doc, QObject* parent)
        : QAbstractItemModel(parent), m_root(nullptr), m_variableGetter(nullptr)
		{
            /*
             * Create root node
             */
            m_root = new ContextMenuItem();
            m_root->setName("__Root");

            /*
             * Create variableGetter node
             */
            m_variableGetter = new ContextMenuItem();
            m_variableGetter->setName("Variables getter");

            /*
             * Create variableSetter node
             */
            m_variableSetter = new ContextMenuItem();
            m_variableSetter->setName("Variables setter");
            /*
             * Populate root model with getter and setter nodes
             */
			m_root->appendChild(m_variableGetter);
            m_root->appendChild(m_variableSetter);

            /*
             * Create enum splitter menu
             */
            m_enumSplitters = new ContextMenuItem();
            m_enumSplitters->setName("Enumerations");
            /*
             * Populate root model with getter and setter nodes
             */
            m_root->appendChild(m_enumSplitters);

			/*
			* Create parameters node
			*/
			m_parameters = new ContextMenuItem();
			m_parameters->setName("Parameters");

			/*
			* Create return node
			*/
			m_returns = new ContextMenuItem();
			m_returns->setName("Returns");
			/*
			* Populate root model with parameters and returns nodes
			*/
			m_root->appendChild(m_parameters);
			m_root->appendChild(m_returns);

			m_paramSetter = new ContextMenuItem();
			m_paramSetter->setName("Setter");

			m_paramGetter = new ContextMenuItem();
			m_paramGetter->setName("Getter");

			m_returnSetter = new ContextMenuItem();
			m_returnSetter->setName("Setter");

			m_returnGetter = new ContextMenuItem();
			m_returnGetter->setName("Getter");

			m_parameters->appendChild(m_paramSetter);
			m_parameters->appendChild(m_paramGetter);

			m_returns->appendChild(m_returnSetter);
			m_returns->appendChild(m_returnGetter);

            /*
             * Create Object Getter/Setter menu
             */
            m_objects = new ContextMenuItem();
            m_objects->setName("Classes");

            m_root->appendChild(m_objects);

            m_objectsGetter = new ContextMenuItem();
            m_objectsGetter->setName("Get attributes");
            m_objects->appendChild(m_objectsGetter);

            m_objectsSetter = new ContextMenuItem();
            m_objectsSetter->setName("Set attributes");
            m_objects->appendChild(m_objectsSetter);

            /*
             * Create Lists menu
             */
            m_lists = new ContextMenuItem();
            m_lists->setName("Lists");
            m_root->appendChild(m_lists);

            m_appends = new ContextMenuItem();
            m_appends->setName("Append");
            m_lists->appendChild(m_appends);

            m_inserts = new ContextMenuItem();
            m_inserts->setName("Insert");
            m_lists->appendChild(m_inserts);

            m_removes = new ContextMenuItem();
            m_removes->setName("Remove");
            m_lists->appendChild(m_removes);

            m_removesAt = new ContextMenuItem();
            m_removesAt->setName("Remove At");
            m_lists->appendChild(m_removesAt);

            m_sizes = new ContextMenuItem();
            m_sizes->setName("Size");
            m_lists->appendChild(m_sizes);

            m_foreachs = new ContextMenuItem();
            m_foreachs->setName("Foreach");

            parseJsonDocument(doc);

            m_hash["/" + m_root->name() + "/Statements"]->appendChild(m_foreachs);
		}

		void ContextMenuModel::parseJsonDocument(const QJsonObject& json)
        {
			parseJsonObj(m_root, json);
		}

		void ContextMenuModel::parseJsonObj(ContextMenuItem *parent, const QJsonObject &js)
		{
			for (const auto& key : js.keys())
			{
				if (key == "categories")
				{
					const auto categories = js[key].toObject();
					for (const auto& categoryKey : categories.keys())
					{
						const auto categoryObj = categories[categoryKey].toObject();
                        auto category = new ContextMenuItem();
						category->setName(categoryKey);
						category->setNodeName(categoryObj["name"].toString());
                        category->setDescription(categoryObj["description"].toString());
                        if (categoryObj.contains("construction"))
                        {
                            QList<qint32> ctrs;

                            for (QJsonValue val : categoryObj["construction"].toArray())
                            {
                                ctrs.append(val.toVariant().toInt());
                            }
                            category->setConstruction(ctrs);
                        }
                        if (parent && categoryObj["inputs"].toInt() == 0 && parent->inputs() != 0)
                            category->setInputs(parent->inputs());
                        else
                            category->setInputs(categoryObj["inputs"].toInt());
                        if (parent && categoryObj["outputs"].toInt() == 0 && parent->outputs() != 0)
                            category->setOutputs(parent->outputs());
                        else
                            category->setOutputs(categoryObj["outputs"].toInt());
                        if (parent && categoryObj["type"].toInt() == 0 && parent->type() != -1)
                            category->setType(parent->type());
                        else
                            category->setType(categoryObj["type"].toInt());
                        if (!categoryObj["instruction_id"].isUndefined())
                        {
                            const auto instruction_id = categoryObj["instruction_id"].toInt();
                            category->setInstructionId(instruction_id);
                        }
						if (parent && !categoryObj["output_names"].isArray() && !parent->outputNames().isEmpty())
							category->setOutputNames(parent->outputNames());
						else
						{
							const auto tab = categoryObj["output_names"].toArray();
							for (const auto &value : tab)
							{
								category->appendOutputName(value.toString());
							}
						}
						if (parent && !categoryObj["input_names"].isArray() && !parent->inputNames().isEmpty())
							category->setInputNames(parent->inputNames());
						else
						{
							const auto tab = categoryObj["input_names"].toArray();
							for (const auto &value : tab)
							{
								category->appendInputName(value.toString());
							}
						}
						category->setFlowIn(categoryObj["in"].toInt());
						category->setFlowOut(categoryObj["out"].toInt());
                        parent->appendChild(category);
                        m_hash[category->fullPath()] = category;
						if (categoryObj.constFind("categories") != categoryObj.constEnd())
							parseJsonObj(category, categoryObj);
					}
				}
			}
		}

		QModelIndex ContextMenuModel::index(int row, int column, const QModelIndex& parent) const
		{
			if (!hasIndex(row, column, parent))
			{
				return {};
			}
			ContextMenuItem *parentItem;

			if (!parent.isValid())
				parentItem = m_root;
			else
				parentItem = static_cast<ContextMenuItem*>(parent.internalPointer());
			const auto childItem = parentItem->child(row);
			if (childItem)
			{
				return createIndex(row, column, childItem);
			}
			return {};
		}

		QModelIndex ContextMenuModel::parent(const QModelIndex& child) const
		{
			if (!child.isValid())
				return {};

			ContextMenuItem *childItem = getItem(child);
			ContextMenuItem *parentItem = childItem->parentItem();

			if (parentItem == m_root)
				return QModelIndex();
			return createIndex(parentItem->row(), 0, parentItem);
		}

		ContextMenuItem *ContextMenuModel::getItem(const QModelIndex &index) const
		{
			if (index.isValid()) {
				ContextMenuItem *item = static_cast<ContextMenuItem*>(index.internalPointer());
				if (item)
					return item;
			}
			return m_root;
		}

		int ContextMenuModel::rowCount(const QModelIndex& parent) const
		{
			ContextMenuItem *parentItem;
			if (parent.column() > 0)
				return 0;

			if (!parent.isValid())
				parentItem = m_root;
			else
				parentItem = static_cast<ContextMenuItem*>(parent.internalPointer());
			return parentItem->childCount();
		}

		int ContextMenuModel::columnCount(const QModelIndex& parent) const
		{
			if (parent.isValid())
				return static_cast<ContextMenuItem*>(parent.internalPointer())->columnCount();
			return m_root->columnCount();
		}

		QVariant ContextMenuModel::data(const QModelIndex& index, int role) const
		{
			if (!index.isValid())
				return QVariant();
			const auto entity = static_cast<ContextMenuItem*>(index.internalPointer());
			switch (role)
			{
			case ITEM:
				return QVariant::fromValue(entity);
			case DESCRIPTION:
				return entity->description();
			case NAME:
			case Qt::DisplayRole:
				return entity->name();
			case INPUTS:
				return entity->inputs();
			case OUTPUTS:
				return entity->outputs();
			case INSTRUCTION_ID:
				return entity->instructionId();
            case CONSTRUCTION:
                return QVariant::fromValue(entity->construction());
			default:
				return QVariant();
            }
        }

        QHash<int, QByteArray> ContextMenuModel::roleNames() const
        {
            QHash<int, QByteArray> hash;
            hash[ITEM] = "item";
            hash[DESCRIPTION] = "description";
            hash[NAME] = "name";
            hash[INPUTS] = "inputs";
            hash[OUTPUTS] = "outputs";
            hash[INSTRUCTION_ID] = "instruction_id";
            hash[CONSTRUCTION] = "construction";
            return hash;
        }

        const QHash<QString, ContextMenuItem *> &ContextMenuModel::instructions() const
        {
            return m_hash;
        }

        void ContextMenuModel::appendVariable(Entity *entity)
        {
            /*
             * Create contextItem for getter
             */
            auto item = new ContextMenuItem();
            item->setName(entity->name());
            item->setDescription(entity->description());
            item->setInputs(0);
            item->setOutputs(1);
            item->setOutputNames({"reference"});
            item->setType(entity->entityType());
            item->setInstructionId(dnai::enums::QInstructionID::GETTER);
            item->setConstruction({entity->id()});

            /*
             * Append variable into getter list
             */
            beginInsertRows(index(0, 0, QModelIndex()), m_variableGetter->childCount(), m_variableGetter->childCount());
            addItem(item, m_variableGetter, entity);
            endInsertRows();

            /*
             * Create contextItem for setter
             */
            item = new ContextMenuItem();
            item->setName(entity->name());
            item->setDescription(entity->description());
            item->setInputs(1);
            item->setOutputs(1);
            item->setFlowIn(1);
            item->setInputNames({"value"});
            item->setFlowOut(1);
            item->setOutputNames({"reference"});
            item->setType(entity->entityType());
            item->setInstructionId(dnai::enums::QInstructionID::SETTER);
            item->setConstruction({entity->id()});

            /*
             * Append variable into setter list
             */
            beginInsertRows(index(1, 0, QModelIndex()), m_variableSetter->childCount(), m_variableSetter->childCount());
            addItem(item, m_variableSetter, entity);
            endInsertRows();
        }

        void ContextMenuModel::appendEnumeration(Entity *entity)
        {
            ContextMenuItem *item = new ContextMenuItem();
            models::EnumType *enu = entity->guiModel<models::EnumType>();

            item->setName(entity->name());
            item->setDescription(entity->description());
            item->setInputs(0);
            item->setOutputs(enu->values().count());
            item->setOutputNames({enu->values()});
            item->setInstructionId(dnai::enums::QInstructionID::ENUM_SPLITTER);
            item->setConstruction({entity->id()});

            beginInsertRows(index(2, 0, QModelIndex()), m_enumSplitters->childCount(), m_enumSplitters->childCount());
            addItem(item, m_enumSplitters, entity);
            endInsertRows();
        }

		void ContextMenuModel::appendParameter(Entity* entity)
		{
			/*
			* Create contextItem for getter
			*/
			auto item = new ContextMenuItem();
			item->setName(entity->name());
			item->setDescription(entity->description());
			item->setInputs(0);
			item->setOutputs(1);
			item->setOutputNames({ "reference" });
			item->setType(entity->entityType());
			item->setInstructionId(dnai::enums::QInstructionID::GETTER);
			item->setConstruction({ static_cast<qint32>(entity->id()) });

			/*
			* Append variable into getter list
			*/
			beginInsertRows(index(0, 0, index(2, 0, QModelIndex())), m_paramGetter->childCount(), m_paramGetter->childCount());
            addItem(item, m_paramGetter, entity);
            endInsertRows();

			/*
			* Create contextItem for setter
			*/
			item = new ContextMenuItem();
			item->setName(entity->name());
			item->setDescription(entity->description());
			item->setInputs(1);
			item->setOutputs(1);
			item->setFlowIn(1);
			item->setInputNames({ "value" });
			item->setFlowOut(1);
			item->setOutputNames({ "reference" });
			item->setType(entity->entityType());
			item->setInstructionId(dnai::enums::QInstructionID::SETTER);
			item->setConstruction({ static_cast<qint32>(entity->id()) });

			/*
			* Append variable into setter list
			*/
			beginInsertRows(index(1, 0, index(2, 0, QModelIndex())), m_paramSetter->childCount(), m_paramSetter->childCount());
            addItem(item, m_paramSetter, entity);
            endInsertRows();
		}

		void ContextMenuModel::appendReturn(Entity* entity)
		{
			/*
			* Create contextItem for getter
			*/
			auto item = new ContextMenuItem();
			item->setName(entity->name());
			item->setDescription(entity->description());
			item->setInputs(0);
			item->setOutputs(1);
			item->setOutputNames({ "reference" });
			item->setType(entity->entityType());
			item->setInstructionId(dnai::enums::QInstructionID::GETTER);
			item->setConstruction({ static_cast<qint32>(entity->id()) });

			/*
			* Append variable into getter list
			*/
			beginInsertRows(index(0, 0, index(3, 0, QModelIndex())), m_returnGetter->childCount(), m_paramGetter->childCount());
            addItem(item, m_returnGetter, entity);
            endInsertRows();

			/*
			* Create contextItem for setter
			*/
			item = new ContextMenuItem();
			item->setName(entity->name());
			item->setDescription(entity->description());
			item->setInputs(1);
			item->setOutputs(1);
			item->setFlowIn(1);
			item->setInputNames({ "value" });
			item->setFlowOut(1);
			item->setOutputNames({ "reference" });
			item->setType(entity->entityType());
			item->setInstructionId(dnai::enums::QInstructionID::SETTER);
			item->setConstruction({ static_cast<qint32>(entity->id()) });

			/*
			* Append variable into setter list
			*/
            beginInsertRows(index(1, 0, index(3, 0, QModelIndex())), m_returnSetter->childCount(), m_paramSetter->childCount());
            addItem(item, m_returnSetter, entity);
            endInsertRows();
		}

		void ContextMenuModel::clearParameters()
		{
			beginRemoveRows(index(0, 0, index(2, 0, QModelIndex())), 0, m_paramGetter->childCount());
            for (ContextMenuItem *curr : m_paramGetter->childrenItem())
            {
                QString fullpath = curr->fullPath();

                m_entity_items.remove(m_items_entity[fullpath]);
                m_items_entity.remove(fullpath);
            }
            m_paramGetter->deleteChildren();
            endRemoveRows();
			beginRemoveRows(index(1, 0, index(2, 0, QModelIndex())), 0, m_paramSetter->childCount());
            for (ContextMenuItem *curr : m_paramSetter->childrenItem())
            {
                QString fullpath = curr->fullPath();

                m_entity_items.remove(m_items_entity[fullpath]);
                m_items_entity.remove(fullpath);
            }
			m_paramSetter->deleteChildren();
			endRemoveRows();
		}

		void ContextMenuModel::clearReturns()
		{
            beginRemoveRows(index(0, 0, index(3, 0, QModelIndex())), 0, m_returnGetter->childCount());
            for (ContextMenuItem *curr : m_returnGetter->childrenItem())
            {
                QString fullpath = curr->fullPath();

                m_entity_items.remove(m_items_entity[fullpath]);
                m_items_entity.remove(fullpath);
            }
			m_returnGetter->deleteChildren();
			endRemoveRows();
			beginRemoveRows(index(1, 0, index(3, 0, QModelIndex())), 0, m_returnSetter->childCount());
            for (ContextMenuItem *curr : m_returnSetter->childrenItem())
            {
                QString fullpath = curr->fullPath();

                m_entity_items.remove(m_items_entity[fullpath]);
                m_items_entity.remove(fullpath);
            }
			m_returnSetter->deleteChildren();
            endRemoveRows();
        }

        void ContextMenuModel::appendObject(Entity *entity)
        {
            models::ObjectType *data = entity->guiModel<models::ObjectType>();

            auto item = new ContextMenuItem();
            item->setName(entity->name());
            item->setDescription("Get attributes of " + entity->name() + " variable");
            item->setInputs(1);
            item->setInputNames({"this"});
            item->setOutputs(data->attributes().count());
            item->setOutputNames(data->attributes());
            item->setType(entity->entityType());
            item->setInstructionId(dnai::enums::QInstructionID::GET_ATTRIBUTES);
            item->setConstruction({entity->id()});

            //append it
            beginInsertRows(index(0, 0, QModelIndex()), m_objectsGetter->childCount(), m_objectsGetter->childCount());
            addItem(item, m_objectsGetter, entity);
            endInsertRows();

            item = new ContextMenuItem();
            item->setName(entity->name());
            item->setDescription("Set attributes of " + entity->name() + " variable");
            item->setInputs(1 + data->attributes().count());
            item->setInputNames(QStringList({"this"}) + data->attributes());
            item->setOutputs(data->attributes().count());
            item->setOutputNames(data->attributes());
            item->setFlowIn(1);
            item->setFlowOut(1);
            item->setType(entity->entityType());
            item->setInstructionId(dnai::enums::QInstructionID::SET_ATTRIBUTES);
            item->setConstruction({entity->id()});

            //append it
            beginInsertRows(index(1, 0, QModelIndex()), m_objectsSetter->childCount(), m_objectsSetter->childCount());
            addItem(item, m_objectsSetter, entity);
            endInsertRows();
        }

        void ContextMenuModel::appendList(Entity *entity)
        {
            models::ListType *data = entity->guiModel<models::ListType>();
            models::Entity *stored = dnai::gcore::HandlerManager::Instance().getEntity(data->storedType());

            /*
             * Foreach
             */
            auto foreachins = new ContextMenuItem();
            foreachins->setName(entity->name());
            foreachins->setDescription("Iterate over " + entity->name() + " elements");
            foreachins->setInputs(1);
            foreachins->setInputNames({"array"});
            foreachins->setOutputs(2);
            foreachins->setOutputNames({"index", "element"});
            foreachins->setFlowIn(1);
            foreachins->setFlowOut(2);
            foreachins->setType(entity->entityType());
            foreachins->setInstructionId(dnai::enums::QInstructionID::FOREACH);
            foreachins->setConstruction({stored->id()});

            addItem(foreachins, m_foreachs, entity);

            /*
             * Insert
             */
            auto insertins = new ContextMenuItem();
            insertins->setName(entity->name());
            insertins->setDescription("Insert element in " + entity->name() + " at index");
            insertins->setInputs(3);
            insertins->setInputNames({"array", "element", "index"});
            insertins->setOutputs(1);
            insertins->setOutputNames({"count"});
            insertins->setFlowIn(1);
            insertins->setFlowOut(1);
            insertins->setType(entity->entityType());
            insertins->setInstructionId(dnai::enums::QInstructionID::INSERT);
            insertins->setConstruction({stored->id()});

            addItem(insertins, m_inserts, entity);

            /*
             * Apend
             */
            auto appendins = new ContextMenuItem();
            appendins->setName(entity->name());
            appendins->setDescription("Append an element in " + entity->name());
            appendins->setInputs(2);
            appendins->setInputNames({"array", "element"});
            appendins->setOutputs(1);
            appendins->setOutputNames({"count"});
            appendins->setFlowIn(1);
            appendins->setFlowOut(1);
            appendins->setType(entity->entityType());
            appendins->setInstructionId(dnai::enums::QInstructionID::APPEND);
            appendins->setConstruction({stored->id()});

            addItem(appendins, m_appends, entity);

            /*
             * Remove
             */
            auto removeins = new ContextMenuItem();
            removeins->setName(entity->name());
            removeins->setDescription("Remove an element from " + entity->name());
            removeins->setInputs(2);
            removeins->setInputNames({"array", "element"});
            removeins->setOutputs(1);
            removeins->setOutputNames({"removed"});
            removeins->setFlowIn(1);
            removeins->setFlowOut(1);
            removeins->setType(entity->entityType());
            removeins->setInstructionId(dnai::enums::QInstructionID::REMOVE);
            removeins->setConstruction({stored->id()});

            addItem(removeins, m_removes, entity);

            /*
             * Remove at
             */
            auto removeAtins = new ContextMenuItem();
            removeAtins->setName(entity->name());
            removeAtins->setDescription("Remove an element at index in " + entity->name());
            removeAtins->setInputs(2);
            removeAtins->setInputNames({"array", "index"});
            removeAtins->setOutputs(1);
            removeAtins->setOutputNames({"removed"});
            removeAtins->setFlowIn(1);
            removeAtins->setFlowOut(1);
            removeAtins->setType(entity->entityType());
            removeAtins->setInstructionId(dnai::enums::QInstructionID::REMOVE_INDEX);
            removeAtins->setConstruction({stored->id()});

            addItem(removeAtins, m_removesAt, entity);

            /*
             * Size
             */
            auto sizeins = new ContextMenuItem();
            sizeins->setName(entity->name());
            sizeins->setDescription("Get the size of a " + entity->name());
            sizeins->setInputs(1);
            sizeins->setInputNames({"array"});
            sizeins->setOutputs(1);
            sizeins->setOutputNames({"count"});
            sizeins->setFlowIn(1);
            sizeins->setFlowOut(1);
            sizeins->setType(entity->entityType());
            sizeins->setInstructionId(dnai::enums::QInstructionID::SIZE);
            sizeins->setConstruction({stored->id()});

            addItem(sizeins, m_sizes, entity);

            /*
             * Binary operators
             */
            auto bopCat = new ContextMenuItem();
            bopCat->setName(entity->name());

            addItem(bopCat, m_hash["/__Root/operators/binaryOperator/others"], entity);

            //access
            auto accessins = new ContextMenuItem();
            accessins->setName("Access");
            accessins->setDescription("Get an element inside a " + entity->name());
            accessins->setInputs(2);
            accessins->setInputNames({"LeftOperand", "RightOperand"});
            accessins->setOutputs(1);
            accessins->setOutputNames({"result"});
            accessins->setType(entity->entityType());
            sizeins->setInstructionId(dnai::enums::QInstructionID::ACCESS);
            sizeins->setConstruction({entity->id(), 2, stored->id()});

            addItem(accessins, bopCat, entity);

            //add
            auto addins = new ContextMenuItem();
            addins->setName("Add");
            addins->setDescription("Add two " + entity->name() + "each other");
            addins->setInputs(2);
            addins->setInputNames({"LeftOperand", "RightOperand"});
            addins->setOutputs(1);
            addins->setOutputNames({"result"});
            addins->setType(entity->entityType());
            addins->setInstructionId(dnai::enums::QInstructionID::ADD);
            addins->setConstruction({entity->id(), entity->id(), entity->id()});

            addItem(addins, bopCat, entity);

            //sub
            auto subins = new ContextMenuItem();
            subins->setName("Substract");
            subins->setDescription("Substract two " + entity->name() + "each other");
            subins->setInputs(2);
            subins->setInputNames({"LeftOperand", "RightOperand"});
            subins->setOutputs(1);
            subins->setOutputNames({"result"});
            subins->setType(entity->entityType());
            subins->setInstructionId(dnai::enums::QInstructionID::SUB);
            subins->setConstruction({entity->id(), entity->id(), entity->id()});

            addItem(subins, bopCat, entity);

            /*
             * Logical operators
             */
            auto logCat = new ContextMenuItem();
            logCat->setName(entity->name());

            addItem(logCat, m_hash["/__Root/operators/binaryOperator/logical"], entity);

            //equal
            auto eqins = new ContextMenuItem();
            eqins->setName("Equal");
            eqins->setDescription("Check if 2 " + entity->name() + " contains same elements");
            eqins->setInputs(2);
            eqins->setInputNames({"LeftOperand", "RightOperand"});
            eqins->setOutputs(1);
            eqins->setOutputNames({"result"});
            eqins->setType(entity->entityType());
            eqins->setInstructionId(dnai::enums::QInstructionID::EQUAL);
            eqins->setConstruction({entity->id(), entity->id()});

            addItem(eqins, logCat, entity);

            //different
            auto difins = new ContextMenuItem();
            difins->setName("Different");
            difins->setDescription("Check if 2 " + entity->name() + " contains different elements");
            difins->setInputs(2);
            difins->setInputNames({"LeftOperand", "RightOperand"});
            difins->setOutputs(1);
            difins->setOutputNames({"result"});
            difins->setType(entity->entityType());
            difins->setInstructionId(dnai::enums::QInstructionID::DIFFERENT);
            difins->setConstruction({entity->id(), entity->id()});

            addItem(difins, logCat, entity);
        }

        void ContextMenuModel::addItem(ContextMenuItem *item, ContextMenuItem *parent, models::Entity *related)
        {
            parent->appendChild(item);

            QString fullpath = item->fullPath(); //fullpath need to be generated after parent have been set

            if (item->instructionId() != core::UNDEFINED_ID)
                m_hash[fullpath] = item;
            if (related != nullptr)
            {
                m_entity_items[related].append(fullpath);
                m_items_entity[fullpath] = related;
            }
        }

        void ContextMenuModel::addItems(Entity *related)
        {
            if (related->parentItem()
                && related->parentItem()->coreModel()->entityType() != ENTITY::FUNCTION
                && related->coreModel()->entityType() == ENTITY::VARIABLE)
            {
                appendVariable(related);
            }
            else if (related->coreModel()->entityType() == ENTITY::ENUM_TYPE)
            {
                appendEnumeration(related);
            }
            else if (related->coreModel()->entityType() == ENTITY::OBJECT_TYPE)
            {
                appendObject(related);
            }
            else if (related->coreModel()->entityType() == ENTITY::LIST_TYPE)
            {
                appendList(related);
            }
        }

        void ContextMenuModel::removeItem(const QString &fullPath)
        {
            ContextMenuItem *torm = m_hash[fullPath];
            models::Entity *related = m_items_entity[fullPath];

            torm->parentItem()->removeOne(torm);
            m_hash.remove(fullPath);
            if (related != nullptr)
            {
                m_items_entity.remove(fullPath);
                m_entity_items[related].removeOne(fullPath);
            }
            delete torm;
        }

        void ContextMenuModel::clearItems(Entity *related)
        {
            QList<QString> pathes = m_entity_items[related];

            for (QString const &curr : pathes)
            {
                removeItem(curr);
            }
        }

        void ContextMenuModel::refreshItems(Entity *related)
        {
            clearItems(related);
            addItems(related);
        }

        void ContextMenuModel::setup()
        {
            QObject::connect(dnai::gcore::HandlerManager::Instance().declarator(), SIGNAL(declared(dnai::models::Entity*)),
                             this, SLOT(onEntityDeclared(dnai::models::Entity*)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().declarator(), SIGNAL(removed(dnai::models::Entity*)),
                             this, SLOT(onEntityRemoved(dnai::models::Entity*)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().declarator(), SIGNAL(renamed(dnai::models::Entity*,QString,QString)),
                             this, SLOT(onEntityRenamed(dnai::models::Entity*,QString,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().enumeration(), SIGNAL(valueSet(dnai::models::Entity*,QString,QString)),
                             this, SLOT(onEnumValueSet(dnai::models::Entity*,QString,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().enumeration(), SIGNAL(valueRemoved(dnai::models::Entity*,QString)),
                             this, SLOT(onEnumValueRemoved(dnai::models::Entity*,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().getClass(), SIGNAL(attributeAdded(models::Entity*,QString,models::Entity*,VISIBILITY)),
                             this, SLOT(onObjectAttributeAdded(models::Entity*,QString,models::Entity*,VISIBILITY)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().getClass(), SIGNAL(attributeRenamed(models::Entity*,QString,QString)),
                             this, SLOT(onObjectAttributeRenamed(models::Entity*,QString,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().getClass(), SIGNAL(attributeRemoved(models::Entity*,QString)),
                             this, SLOT(onObjectAttributeRemoved(models::Entity*,QString)));
        }

        void ContextMenuModel::onEntityDeclared(Entity *declared)
        {
            addItems(declared);
        }

        void ContextMenuModel::onEntityRemoved(Entity *removed)
        {
            clearItems(removed);
        }

        void ContextMenuModel::onEntityRenamed(Entity *entity, QString name, QString newname)
        {
            Q_UNUSED(name)
            Q_UNUSED(newname)

            refreshItems(entity);
        }

        void ContextMenuModel::onEnumValueSet(Entity *enumeration, QString name, QString value)
        {
            Q_UNUSED(name)
            Q_UNUSED(value)

            refreshItems(enumeration);
        }

        void ContextMenuModel::onEnumValueRemoved(Entity *enumeration, QString name)
        {
            Q_UNUSED(name)

            refreshItems(enumeration);
        }

        void ContextMenuModel::onObjectAttributeAdded(Entity *obj, QString name, Entity *type, VISIBILITY visi)
        {
            Q_UNUSED(name)
            Q_UNUSED(type)
            Q_UNUSED(visi)

            refreshItems(obj);
        }

        void ContextMenuModel::onObjectAttributeRenamed(Entity *obj, QString name, QString newName)
        {
            Q_UNUSED(obj)
            Q_UNUSED(name)
            Q_UNUSED(newName)

            refreshItems(obj);
        }

        void ContextMenuModel::onObjectAttributeRemoved(Entity *obj, QString name)
        {
            Q_UNUSED(name)

            refreshItems(obj);
        }
	}
}
