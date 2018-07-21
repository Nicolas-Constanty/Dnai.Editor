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

        const QMap<QString, QString> &ContextMenuItem::inputs() const
		{
            return m_inputs;
        }

        const QMap<QString, QString> &ContextMenuItem::inputsDisplayNames() const
        {
            return m_inputDisplayNames;
        }

        int ContextMenuItem::inputSize() const
        {
            return m_inputs.size();
        }

        const QMap<QString, QString> &ContextMenuItem::outputs() const
		{
            return m_outputs;
        }

        const QMap<QString, QString> &ContextMenuItem::outputsDisplayNames() const
        {
            return m_outputDisplayNames;
        }

        int ContextMenuItem::outputSize() const
        {
            return m_outputs.size();
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

        QStringList ContextMenuItem::inputNames() const
		{
            return m_inputs.keys();
		}

        QStringList ContextMenuItem::outputNames() const
		{
            return m_outputs.keys();
        }

        QString ContextMenuItem::getInput(QString name) const
        {
            return m_inputs[name];
        }

        QString ContextMenuItem::getOutput(QString name) const
        {
            return m_outputs[name];
        }

        QString ContextMenuItem::getInputDisplayName(QString name) const
        {
            return m_inputDisplayNames[name];
        }

        QString ContextMenuItem::getOutputDisplayName(QString name) const
        {
            return m_outputDisplayNames[name];
        }

        QString ContextMenuItem::fullPath() const
        {
            return (parentItem() != nullptr ? parentItem()->fullPath() : "") + "/" + name();
        }

        void ContextMenuItem::addInput(const QString &name, const QString &type, const QString &displayName)
        {
            m_inputs[name] = type;
            m_inputDisplayNames[name] = displayName;
            emit inputNamesChanged(inputNames());
            emit inputSizeChanged(inputSize());
        }

        void ContextMenuItem::addInputs(const QMap<QString, QString> &inputs, const QMap<QString, QString> &displayNames)
        {
            m_inputs.unite(inputs);
            m_inputDisplayNames.unite(displayNames);
            emit inputNamesChanged(inputNames());
            emit inputSizeChanged(inputSize());
        }

        void ContextMenuItem::addOutput(const QString &name, const QString &type, const QString &displayName)
        {
            m_outputs[name] = type;
            m_outputDisplayNames[name] = displayName;
            emit outputNamesChanged(outputNames());
            emit outputSizeChanged(outputSize());
        }

        void ContextMenuItem::addOutputs(const QMap<QString, QString> &outputs, const QMap<QString, QString> &displayNames)
        {
            m_outputs.unite(outputs);
            m_outputDisplayNames.unite(displayNames);
            emit outputNamesChanged(outputNames());
            emit outputSizeChanged(outputSize());
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

        ContextMenuModel::ContextMenuModel(QObject* parent) :
            QAbstractItemModel(parent),
            m_root(nullptr),
            m_functions(nullptr),
            m_lists(nullptr),
            m_classes(nullptr),
            m_variables(nullptr),
            m_enumerations(nullptr),
            m_functionRebuilding(false)
		{

		}

        ContextMenuModel::ContextMenuModel(const QJsonObject &doc, QObject* parent) :
            QAbstractItemModel(parent)
		{
            /*
             * Create root node
             */
            m_root = new ContextMenuItem();
            m_root->setName("__Root");

            //function category
            m_functions = new ContextMenuItem();
            m_functions->setName("Functions");
            m_root->appendChild(m_functions);

            //list category
            m_lists = new ContextMenuItem();
            m_lists->setName("Lists");
            m_root->appendChild(m_lists);

            //class category
            m_classes = new ContextMenuItem();
            m_classes->setName("Classes");
            m_root->appendChild(m_classes);

            //variable category
            m_variables = new ContextMenuItem();
            m_variables->setName("Variables");
            m_root->appendChild(m_variables);

            //enumcategory
            m_enumerations = new ContextMenuItem();
            m_enumerations->setName("Enumerations");
            m_root->appendChild(m_enumerations);

            parseJsonDocument(doc);
        }

		void ContextMenuModel::parseJsonDocument(const QJsonObject& json)
        {
			parseJsonObj(m_root, json);
		}

		void ContextMenuModel::parseJsonObj(ContextMenuItem *parent, const QJsonObject &js)
		{
            qDebug() << "Parse menu";
			for (const auto& key : js.keys())
            {
                qDebug() << "Curr key" << key;
				if (key == "categories")
				{
                    qDebug() << "Found categories";

					const auto categories = js[key].toObject();
					for (const auto& categoryKey : categories.keys())
					{
						const auto categoryObj = categories[categoryKey].toObject();
                        auto category = new ContextMenuItem();
						category->setName(categoryKey);
						category->setNodeName(categoryObj["name"].toString());
                        category->setDescription(categoryObj["description"].toString());

                        qDebug() << "Creating category" << categoryKey;

                        if (categoryObj.contains("construction"))
                        {
                            QList<qint32> ctrs;

                            for (QJsonValue val : categoryObj["construction"].toArray())
                            {
                                ctrs.append(val.toVariant().toInt());
                            }
                            category->setConstruction(ctrs);
                        }

                        if (parent && categoryObj["type"].toInt() == 0 && parent->type() != -1)
                            category->setType(parent->type());
                        else
                            category->setType(categoryObj["type"].toInt());

                        if (!categoryObj["instruction_id"].isUndefined())
                        {
                            const auto instruction_id = categoryObj["instruction_id"].toInt();
                            category->setInstructionId(instruction_id);
                        }

                        if (parent && parent->inputs().size() > 0)
                        {
                            category->addInputs(parent->inputs(), parent->inputsDisplayNames());
                        }

                        if (categoryObj["inputs"].isArray())
                        {
                            for (QJsonValue input : categoryObj["inputs"].toArray())
                            {
                                QJsonObject obj = input.toObject();

                                category->addInput(obj["name"].toString(), obj["type"].toString(), obj["display_name"].toString());
                            }
                        }

                        if (parent && parent->outputs().size() > 0)
                        {
                            category->addOutputs(parent->outputs(), parent->outputsDisplayNames());
                        }

                        if (categoryObj["outputs"].isArray())
                        {
                            for (QJsonValue output : categoryObj["outputs"].toArray())
                            {
                                QJsonObject obj = output.toObject();

                                category->addOutput(obj["name"].toString(), obj["type"].toString(), obj["display_name"].toString());
                            }
                        }

						category->setFlowIn(categoryObj["in"].toInt());
						category->setFlowOut(categoryObj["out"].toInt());
                        parent->appendChild(category);
                        m_hash[category->fullPath()] = category;

                        qDebug() << "Register: " << category->fullPath();

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
                return entity->inputs().size();
			case OUTPUTS:
                return entity->outputs().size();
			case INSTRUCTION_ID:
				return entity->instructionId();
            case TYPE:
                return entity->type();
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
            hash[TYPE] = "type_id";
            return hash;
        }

        const QHash<QString, ContextMenuItem *> &ContextMenuModel::instructions() const
        {
            return m_hash;
        }

        void ContextMenuModel::appendVariable(Entity *entity)
        {
            QString varType = entity->guiModel<Variable>()->varType().toString();

            /*
             * Variable getter
             */
            ContextMenuItem *getter = new ContextMenuItem();

            getter->setName("Get " + entity->fullName());
            getter->setDescription(entity->description());
            getter->addOutput("reference", varType, "Value");
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({entity->id()});

            addItem(getter, m_variables, entity);

            /*
             * Variable setter
             */
            ContextMenuItem *setter = new ContextMenuItem();

            setter->setName("Set " + entity->fullName());
            setter->setDescription(entity->description());
            setter->addInput("value", varType, "Value");
            setter->addOutput("reference", varType, "Value");
            setter->setFlowIn(1);
            setter->setFlowOut(1);
            setter->setInstructionId(dnai::enums::QInstructionID::SETTER);
            setter->setConstruction({entity->id()});

            addItem(setter, m_variables, entity);
        }

        void ContextMenuModel::appendEnumeration(Entity *entity)
        {
            models::EnumType *enu = entity->guiModel<models::EnumType>();
            QString enuType = entity->guid().toString();

            ContextMenuItem *splitter = new ContextMenuItem();
            splitter->setName(entity->fullName());
            splitter->setDescription(entity->description());
            for (QString curr : enu->values())
            {
                splitter->addOutput(curr, enuType, curr);
            }
            splitter->setInstructionId(dnai::enums::QInstructionID::ENUM_SPLITTER);
            splitter->setConstruction({entity->id()});

            addItem(splitter, m_enumerations, entity);

            ContextMenuItem *log_b_op = m_hash["/" + m_root->name() + "/operators/binaryOperator/logical"];

            ContextMenuItem *enum_log_cat = new ContextMenuItem();
            enum_log_cat->setName(entity->fullName());
            addItem(enum_log_cat, log_b_op, entity);

            ContextMenuItem *eq = new ContextMenuItem();
            eq->setName("Equal");
            eq->setDescription("Check if two enum values are equal");
            eq->addInput("LeftOperand", enuType, "Value 1");
            eq->addInput("RightOperand", enuType, "Value 2");
            eq->addOutput("result", "{907ad50a-8f54-51ea-8c68-479d1d90a699}", "Result");
            eq->setInstructionId(dnai::enums::QInstructionID::EQUAL);
            eq->setConstruction({entity->id(), entity->id()});
            addItem(eq, enum_log_cat, entity);

            ContextMenuItem *ne = new ContextMenuItem();
            ne->setName("Different");
            ne->setDescription("Check if two enum values are different");
            ne->addInput("LeftOperand", enuType, "Value 1");
            ne->addInput("RightOperand", enuType, "Value 2");
            ne->addOutput("result", "{907ad50a-8f54-51ea-8c68-479d1d90a699}", "Result");
            ne->setInstructionId(dnai::enums::QInstructionID::DIFFERENT);
            ne->setConstruction({entity->id(), entity->id()});
            addItem(ne, enum_log_cat, entity);
        }

		void ContextMenuModel::appendParameter(Entity* entity)
		{
            QString varType = entity->guiModel<Variable>()->varType().toString();
            ContextMenuItem *parameters = m_hash["/" + m_root->name() + "/" + m_functions->name() + "/" + entity->parentItem()->fullName() + "/Parameters"];

			/*
			* Create contextItem for getter
			*/
            ContextMenuItem *getter = new ContextMenuItem();
            getter->setName("Get " + entity->name());
            getter->setDescription(entity->description());
            getter->addOutput("reference", varType, "Value");
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({ entity->id() });

            addItem(getter, parameters, entity);

			/*
			* Create contextItem for setter
			*/
            ContextMenuItem *setter = new ContextMenuItem();
            setter->setName("Set " + entity->name());
            setter->setDescription(entity->description());
            setter->addInput("value", varType, "Value");
            setter->addOutput("reference", varType, "Value");
            setter->setFlowIn(1);
            setter->setFlowOut(1);
            setter->setInstructionId(dnai::enums::QInstructionID::SETTER);
            setter->setConstruction({ entity->id() });

            addItem(setter, parameters, entity);
        }

        void ContextMenuModel::appendReturn(Entity* entity)
        {
            QString varType = entity->guiModel<Variable>()->varType().toString();
            ContextMenuItem *returns = m_hash["/" + m_root->name() + "/" + m_functions->name() + "/" + entity->parentItem()->fullName() + "/Returns"];

            /*
            * Create contextItem for getter
            */
            ContextMenuItem *getter = new ContextMenuItem();
            getter->setName("Get " + entity->name());
            getter->setDescription(entity->description());
            getter->addOutput("reference", varType, "Value");
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({ entity->id() });

            addItem(getter, returns, entity);

            /*
            * Create contextItem for setter
            */
            ContextMenuItem *setter = new ContextMenuItem();
            setter->setName("Set " + entity->name());
            setter->setDescription(entity->description());
            setter->addInput("value", varType, "Value");
            setter->addOutput("reference", varType, "Value");
            setter->setFlowIn(1);
            setter->setFlowOut(1);
            setter->setInstructionId(dnai::enums::QInstructionID::SETTER);
            setter->setConstruction({ entity->id() });

            addItem(setter, returns, entity);
        }

        void ContextMenuModel::appendObject(Entity *entity)
        {
            models::ObjectType *data = entity->guiModel<models::ObjectType>();

            ContextMenuItem *entityCategory = new ContextMenuItem();
            entityCategory->setName(entity->fullName());
            addItem(entityCategory, m_classes, entity);

            /*
             * Get attributes
             */
            ContextMenuItem *getAttributes = new ContextMenuItem();
            getAttributes->setName("Get attributes");
            getAttributes->setDescription("Get attributes of " + entity->name() + " variable");
            getAttributes->addInput("this", entity->guid().toString(), "Target");
            getAttributes->setInstructionId(dnai::enums::QInstructionID::GET_ATTRIBUTES);
            getAttributes->setConstruction({entity->id()});

            /*
             * Set attributes
             */
            ContextMenuItem *setAttributes = new ContextMenuItem();
            setAttributes->setName("Set attributes");
            setAttributes->setDescription("Set attributes of " + entity->name() + " variable");
            setAttributes->addInput("this", entity->guid().toString(), "Target");
            setAttributes->setFlowIn(1);
            setAttributes->setFlowOut(1);
            setAttributes->setType(entity->entityType());
            setAttributes->setInstructionId(dnai::enums::QInstructionID::SET_ATTRIBUTES);
            setAttributes->setConstruction({entity->id()});

            for (const QString &curr : data->attributes())
            {
                QString attrType = dnai::gcore::HandlerManager::Instance().getEntity(data->getAttribute(curr))->guid().toString();

                getAttributes->addOutput(curr, attrType, curr);
                setAttributes->addInput(curr, attrType, curr);
                setAttributes->addOutput(curr, attrType, curr);
            }

            addItem(getAttributes, entityCategory, entity);
            addItem(setAttributes, entityCategory, entity);
        }

        void ContextMenuModel::appendList(Entity *entity)
        {
            models::ListType *data = entity->guiModel<models::ListType>();
            models::Entity *stored = dnai::gcore::HandlerManager::Instance().getEntity(data->storedType());

            QString listType = entity->guid().toString();
            QString storedType = stored->guid().toString();

            ContextMenuItem *entityCategory = new ContextMenuItem();
            entityCategory->setName(entity->fullName());
            addItem(entityCategory, m_lists, entity);

            /*
             * Foreach
             */
            ContextMenuItem *foreachins = new ContextMenuItem();
            foreachins->setName("Foreach");
            foreachins->setDescription("Iterate over " + entity->name() + " elements");
            foreachins->addInput("array", listType, "Target");
            foreachins->addOutput("index", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Index"); //integer
            foreachins->addOutput("element", storedType, "Element");
            foreachins->setFlowIn(1);
            foreachins->setFlowOut(2);
            foreachins->setInstructionId(dnai::enums::QInstructionID::FOREACH);
            foreachins->setConstruction({stored->id()});

            addItem(foreachins, entityCategory, entity);

            /*
             * Insert
             */
            ContextMenuItem *insertins = new ContextMenuItem();
            insertins->setName("Insert at");
            insertins->setDescription("Insert element in " + entity->name() + " at index");
            insertins->addInput("array", listType, "Target");
            insertins->addInput("element", storedType, "Element");
            insertins->addInput("index", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Index"); //integer
            insertins->addOutput("count", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Size"); //integer
            insertins->setFlowIn(1);
            insertins->setFlowOut(1);
            insertins->setType(entity->entityType());
            insertins->setInstructionId(dnai::enums::QInstructionID::INSERT);
            insertins->setConstruction({stored->id()});

            addItem(insertins, entityCategory, entity);

            /*
             * Apend
             */
            ContextMenuItem *appendins = new ContextMenuItem();
            appendins->setName("Append");
            appendins->setDescription("Append an element in " + entity->name());
            appendins->addInput("array", listType, "Target");
            appendins->addInput("element", storedType, "Element");
            appendins->addOutput("count", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Size"); //integer
            appendins->setFlowIn(1);
            appendins->setFlowOut(1);
            appendins->setType(entity->entityType());
            appendins->setInstructionId(dnai::enums::QInstructionID::APPEND);
            appendins->setConstruction({stored->id()});

            addItem(appendins, entityCategory, entity);

            /*
             * Remove
             */
            ContextMenuItem *removeins = new ContextMenuItem();
            removeins->setName("Remove");
            removeins->setDescription("Remove an element from " + entity->name());
            removeins->addInput("array", listType, "Target");
            removeins->addInput("element", storedType, "Element");
            removeins->addOutput("removed", storedType, "Removed");
            removeins->setFlowIn(1);
            removeins->setFlowOut(1);
            removeins->setType(entity->entityType());
            removeins->setInstructionId(dnai::enums::QInstructionID::REMOVE);
            removeins->setConstruction({stored->id()});

            addItem(removeins, entityCategory, entity);

            /*
             * Remove at
             */
            ContextMenuItem *removeAtins = new ContextMenuItem();
            removeAtins->setName("Remove at");
            removeAtins->setDescription("Remove an element at index in " + entity->name());
            removeAtins->addInput("array", listType, "Target");
            removeAtins->addInput("index", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Index");
            removeAtins->addOutput("removed", storedType, "Removed");
            removeAtins->setFlowIn(1);
            removeAtins->setFlowOut(1);
            removeAtins->setType(entity->entityType());
            removeAtins->setInstructionId(dnai::enums::QInstructionID::REMOVE_INDEX);
            removeAtins->setConstruction({stored->id()});

            addItem(removeAtins, entityCategory, entity);

            /*
             * Size
             */
            ContextMenuItem *sizeins = new ContextMenuItem();
            sizeins->setName("Size");
            sizeins->setDescription("Get the size of a " + entity->name());
            sizeins->addInput("array", listType, "Target");
            sizeins->addOutput("count", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Size"); //integer
            sizeins->setType(entity->entityType());
            sizeins->setInstructionId(dnai::enums::QInstructionID::SIZE);
            sizeins->setConstruction({stored->id()});

            addItem(sizeins, entityCategory, entity);

            /*
             * Clear
             */
            ContextMenuItem *clearins = new ContextMenuItem();
            clearins->setName("Clear");
            clearins->setDescription("Clear an array from its elements");
            clearins->addInput("array", listType, "Target");
            clearins->setFlowIn(1);
            clearins->setFlowOut(1);
            clearins->setType(entity->entityType());
            clearins->setInstructionId(dnai::enums::QInstructionID::CLEAR);
            clearins->setConstruction({stored->id()});

            addItem(clearins, entityCategory, entity);

            /*
             * Fill
             */
            ContextMenuItem *fillins = new ContextMenuItem();
            fillins->setName("Fill");
            fillins->setDescription("Fill an array with an elements n times");
            fillins->addInput("array", listType, "Target");
            fillins->addInput("element", storedType, "Element");
            fillins->addInput("count", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Count");
            fillins->addOutput("count", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Size");
            fillins->setFlowIn(1);
            fillins->setFlowOut(1);
            fillins->setType(entity->entityType());
            fillins->setInstructionId(dnai::enums::QInstructionID::FILL);
            fillins->setConstruction({stored->id()});

            addItem(fillins, entityCategory, entity);

            /*
             * Set value at
             */
            ContextMenuItem *setvalueatins = new ContextMenuItem();
            setvalueatins->setName("Set value at");
            setvalueatins->setDescription("Set the value of a " + entity->name() + " at a specific index");
            setvalueatins->addInput("array", listType, "Target");
            setvalueatins->addInput("value", storedType, "Value");
            setvalueatins->addInput("index", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Index");
            setvalueatins->addOutput("value", storedType, "Value");
            setvalueatins->setFlowIn(1);
            setvalueatins->setFlowOut(1);
            setvalueatins->setType(entity->entityType());
            setvalueatins->setInstructionId(dnai::enums::QInstructionID::SET_VALUE_AT);
            setvalueatins->setConstruction({stored->id()});

            addItem(setvalueatins, entityCategory, entity);

            /*
             * Binary operators
             */
            auto bopCat = new ContextMenuItem();
            bopCat->setName(entity->fullName());

            addItem(bopCat, m_hash["/__Root/operators/binaryOperator/others"], entity);

            //access
            auto accessins = new ContextMenuItem();
            accessins->setName("Access");
            accessins->setDescription("Get an element inside a " + entity->name());
            accessins->addInput("LeftOperand", listType, "Target");
            accessins->addInput("RightOperand", "{149e81c5-fc6e-5cc7-a0a6-6f736a6487ca}", "Index");
            accessins->addOutput("result", storedType, "Element");
            accessins->setType(entity->entityType());
            accessins->setInstructionId(dnai::enums::QInstructionID::ACCESS);
            accessins->setConstruction({entity->id(), 2, stored->id()});

            addItem(accessins, bopCat, entity);

            //add
            auto addins = new ContextMenuItem();
            addins->setName("Add");
            addins->setDescription("Add two " + entity->name() + "each other");
            addins->addInput("LeftOperand", listType, "List 1");
            addins->addInput("RightOperand", listType, "List 2");
            addins->addOutput("result", listType, "Result");
            addins->setType(entity->entityType());
            addins->setInstructionId(dnai::enums::QInstructionID::ADD);
            addins->setConstruction({entity->id(), entity->id(), entity->id()});

            addItem(addins, bopCat, entity);

            //sub
            auto subins = new ContextMenuItem();
            subins->setName("Substract");
            subins->setDescription("Substract two " + entity->name() + "each other");
            subins->addInput("LeftOperand", listType, "Ref list");
            subins->addInput("RightOperand", listType, "Sub list");
            subins->addOutput("result", listType, "Result");
            subins->setType(entity->entityType());
            subins->setInstructionId(dnai::enums::QInstructionID::SUB);
            subins->setConstruction({entity->id(), entity->id(), entity->id()});

            addItem(subins, bopCat, entity);

            /*
             * Logical operators
             */
            auto logCat = new ContextMenuItem();
            logCat->setName(entity->fullName());

            addItem(logCat, m_hash["/__Root/operators/binaryOperator/logical"], entity);

            //equal
            auto eqins = new ContextMenuItem();
            eqins->setName("Equal");
            eqins->setDescription("Check if 2 " + entity->name() + " contains same elements");
            eqins->addInput("LeftOperand", listType, "List 1");
            eqins->addInput("RightOperand", listType, "List 2");
            eqins->addOutput("result", "{907ad50a-8f54-51ea-8c68-479d1d90a699}", "Result"); //boolean
            eqins->setType(entity->entityType());
            eqins->setInstructionId(dnai::enums::QInstructionID::EQUAL);
            eqins->setConstruction({entity->id(), entity->id()});

            addItem(eqins, logCat, entity);

            //different
            auto difins = new ContextMenuItem();
            difins->setName("Different");
            difins->setDescription("Check if 2 " + entity->name() + " contains different elements");
            difins->addInput("LeftOperand", listType, "List 1");
            difins->addInput("RightOperand", listType, "List 2");
            difins->addOutput("result", "{907ad50a-8f54-51ea-8c68-479d1d90a699}", "Result"); //boolean
            difins->setType(entity->entityType());
            difins->setInstructionId(dnai::enums::QInstructionID::DIFFERENT);
            difins->setConstruction({entity->id(), entity->id()});

            addItem(difins, logCat, entity);
        }

        void ContextMenuModel::appendFunction(Entity *entity)
        {
            m_functionRebuilding = true;

            models::Function *data = entity->guiModel<models::Function>();

            ContextMenuItem *funcCat = new ContextMenuItem();
            funcCat->setName(entity->fullName());
            addItem(funcCat, m_functions, entity);

            ContextMenuItem *parameters = new ContextMenuItem();
            parameters->setName("Parameters");
            addItem(parameters, funcCat, entity);

            ContextMenuItem *returns = new ContextMenuItem();
            returns->setName("Returns");
            addItem(returns, funcCat, entity);

            /*
             * Call
             */
            ContextMenuItem *callfuncins = new ContextMenuItem();
            callfuncins->setName("Call");
            callfuncins->setDescription("Call function " + entity->fullName());

            for (models::Entity *curr : data->inputs())
            {
                callfuncins->addInput(curr->name(), curr->guiModel<Variable>()->varType().toString(), curr->name());
                refreshItems(curr);
            }

            for (models::Entity *curr : data->outputs())
            {
                callfuncins->addOutput(curr->name(), curr->guiModel<Variable>()->varType().toString(), curr->name());
                refreshItems(curr);
            }

            callfuncins->setFlowIn(1);
            callfuncins->setFlowOut(1);
            callfuncins->setType(entity->entityType());
            callfuncins->setInstructionId(dnai::enums::QInstructionID::FUNCTION_CALL);
            callfuncins->setConstruction({entity->id()});

            addItem(callfuncins, funcCat, entity);

            m_functionRebuilding = false;
        }

        void ContextMenuModel::addItem(ContextMenuItem *item, ContextMenuItem *parent, models::Entity *related)
        {
            beginInsertRows(parent->idxmodel(), parent->childCount(), parent->childCount());
            parent->appendChild(item);
            endInsertRows();

            QString fullpath = item->fullPath(); //fullpath need to be generated after parent have been set

            m_hash[fullpath] = item;
            if (related != nullptr)
            {
                m_entity_items[related].append(fullpath);
                m_items_entity[fullpath] = related;
            }
        }

        void ContextMenuModel::addItems(Entity *related)
        {
            switch (related->coreModel()->entityType())
            {
            case ENTITY::ENUM_TYPE:
                appendEnumeration(related);
                break;
            case ENTITY::OBJECT_TYPE:
                appendObject(related);
                break;
            case ENTITY::LIST_TYPE:
                appendList(related);
                break;
            case ENTITY::FUNCTION:
                appendFunction(related);
                break;
            case ENTITY::VARIABLE: {
                if (related->parentItem() && related->parentItem()->coreModel()->entityType() == ENTITY::FUNCTION)
                {
                    models::Entity *func = related->parentItem();
                    models::Function *data = func->guiModel<models::Function>();

                    if (data->hasInput(related->name()))
                    {
                        appendParameter(related);
                    }
                    else if (data->hasOutput(related->name()))
                    {
                        appendReturn(related);
                    }
                    else
                    {
                        appendVariable(related);
                    }
                    if (!m_functionRebuilding)
                        refreshItems(func);
                }
                else
                {
                    appendVariable(related);
                }
                break;
            }
            default: break;
            }
        }

        void ContextMenuModel::removeItem(const QString &fullPath)
        {
            ContextMenuItem *torm = m_hash[fullPath];
            models::Entity *related = m_items_entity[fullPath];

            if (torm)
            {
                if (torm->parentItem())
                {
                    torm->parentItem()->removeOne(torm);
                }
                m_hash.remove(fullPath);
            }
            if (related != nullptr)
            {
                m_items_entity.remove(fullPath);
                m_entity_items[related].removeOne(fullPath);
            }
            beginRemoveRows(torm->idxmodel(), 0, torm->childCount());
            torm->removeChildren();
            endRemoveRows();
            delete torm;
        }

        void ContextMenuModel::clearItems(Entity *related)
        {
            QList<QString> pathes = m_entity_items[related];

            //need to reverse iterate in order to start removing leaf of context menu
            for (QList<QString>::reverse_iterator it = pathes.rbegin(), end = pathes.rend(); it != end; ++it)
            {
                removeItem(*it);
            }
        }

        void ContextMenuModel::refreshItems(Entity *related)
        {
            clearItems(related);
            addItems(related);
            QList<models::gui::Instruction *> instructions;

            for (QString const &curr : m_entity_items[related])
            {
                for (models::gui::Instruction *torebuild : dnai::gcore::HandlerManager::Instance().function()->instruction()->getInstructionsOfPath(curr))
                {
                    instructions.append(torebuild);
                }
            }

            dnai::gcore::HandlerManager::Instance().function()->rebuildInstructions(instructions);
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
            QObject::connect(dnai::gcore::HandlerManager::Instance().List(), SIGNAL(typeSet(dnai::models::Entity*,dnai::models::Entity*)),
                             this, SLOT(onListTypeSet(dnai::models::Entity*,dnai::models::Entity*)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().function(), SIGNAL(parameterSet(dnai::models::Entity*,QString)),
                             this, SLOT(onParameterSet(dnai::models::Entity*,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().function(), SIGNAL(returnSet(dnai::models::Entity*,QString)),
                             this, SLOT(onReturnSet(dnai::models::Entity*,QString)));
            QObject::connect(dnai::gcore::HandlerManager::Instance().variable(), SIGNAL(typeSet(dnai::models::Entity*,dnai::models::Entity*)),
                             this, SLOT(onVariableTypeSet(dnai::models::Entity*,dnai::models::Entity*)));
        }

        void ContextMenuModel::onEntityDeclared(Entity *declared)
        {
            addItems(declared);
        }

        void ContextMenuModel::onEntityRemoved(Entity *removed)
        {
            clearItems(removed);

            if (removed->entityType() == static_cast<qint32>(ENTITY::FUNCTION))
            {
                models::Function *data = removed->guiModel<models::Function>();

                for (models::Entity *curr : data->inputs())
                {
                    clearItems(curr);
                }

                for (models::Entity *curr : data->outputs())
                {
                    clearItems(curr);
                }
            }
            if (removed->parentItem() && removed->parentItem()->entityType() == static_cast<qint32>(ENTITY::FUNCTION))
            {
                refreshItems(removed->parentItem());
            }
        }

        void ContextMenuModel::onEntityRenamed(Entity *entity, QString name, QString newname)
        {
            Q_UNUSED(name)
            Q_UNUSED(newname)

            if (entity->parentItem()->entityType() == static_cast<qint32>(ENTITY::FUNCTION))
            {
                refreshItems(entity->parentItem());
            }
            else
            {
                refreshItems(entity);
            }
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

        void ContextMenuModel::onListTypeSet(Entity *lst, Entity *type)
        {
            Q_UNUSED(type)

            refreshItems(lst);
        }

        void ContextMenuModel::onParameterSet(Entity *func, QString param)
        {
            refreshItems(func);
        }

        void ContextMenuModel::onReturnSet(Entity *func, QString ret)
        {
            refreshItems(func);
        }

        void ContextMenuModel::onVariableTypeSet(Entity *var, Entity *type)
        {
            Q_UNUSED(type);
            refreshItems(var);
        }
	}
}
