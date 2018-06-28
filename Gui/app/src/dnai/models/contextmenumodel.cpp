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

        ContextMenuModel::ContextMenuModel(QObject* parent) :
            QAbstractItemModel(parent),
            m_root(nullptr),
            m_functions(nullptr),
            m_lists(nullptr),
            m_classes(nullptr),
            m_variables(nullptr),
            m_enumerations(nullptr)
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
            /*
             * Variable getter
             */
            ContextMenuItem *getter = new ContextMenuItem();

            getter->setName("Get " + entity->fullName());
            getter->setDescription(entity->description());
            getter->setInputs(0);
            getter->setOutputs(1);
            getter->setOutputNames({"reference"});
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({entity->id()});

            addItem(getter, m_variables, entity);

            /*
             * Variable setter
             */
            ContextMenuItem *setter = new ContextMenuItem();

            setter->setName("Set " + entity->fullName());
            setter->setDescription(entity->description());
            setter->setInputs(1);
            setter->setInputNames({"value"});
            setter->setOutputs(1);
            setter->setOutputNames({"reference"});
            setter->setFlowIn(1);
            setter->setFlowOut(1);
            setter->setInstructionId(dnai::enums::QInstructionID::SETTER);
            setter->setConstruction({entity->id()});

            addItem(setter, m_variables, entity);
        }

        void ContextMenuModel::appendEnumeration(Entity *entity)
        {
            models::EnumType *enu = entity->guiModel<models::EnumType>();
            ContextMenuItem *splitter = new ContextMenuItem();

            splitter->setName(entity->fullName());
            splitter->setDescription(entity->description());
            splitter->setInputs(0);
            splitter->setOutputs(enu->values().count());
            splitter->setOutputNames({enu->values()});
            splitter->setInstructionId(dnai::enums::QInstructionID::ENUM_SPLITTER);
            splitter->setConstruction({entity->id()});

            addItem(splitter, m_enumerations, entity);
        }

		void ContextMenuModel::appendParameter(Entity* entity)
		{
            ContextMenuItem *parameters = m_hash["/" + m_root->name() + "/" + m_functions->name() + "/" + entity->parentItem()->fullName() + "/Parameters"];

			/*
			* Create contextItem for getter
			*/
            ContextMenuItem *getter = new ContextMenuItem();
            getter->setName("Get " + entity->name());
            getter->setDescription(entity->description());
            getter->setInputs(0);
            getter->setOutputs(1);
            getter->setOutputNames({ "reference" });
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({ static_cast<qint32>(entity->id()) });

            addItem(getter, parameters, entity);

			/*
			* Create contextItem for setter
			*/
            ContextMenuItem *setter = new ContextMenuItem();
            setter->setName("Set " + entity->name());
            setter->setDescription(entity->description());
            setter->setInputs(1);
            setter->setInputNames({ "value" });
            setter->setOutputs(1);
            setter->setOutputNames({ "reference" });
            setter->setFlowIn(1);
            setter->setFlowOut(1);
            setter->setInstructionId(dnai::enums::QInstructionID::SETTER);
            setter->setConstruction({ entity->id() });

            addItem(setter, parameters, entity);
        }

        void ContextMenuModel::appendReturn(Entity* entity)
        {
            ContextMenuItem *returns = m_hash["/" + m_root->name() + "/" + m_functions->name() + "/" + entity->parentItem()->fullName() + "/Returns"];

            /*
            * Create contextItem for getter
            */
            ContextMenuItem *getter = new ContextMenuItem();
            getter->setName("Get " + entity->name());
            getter->setDescription(entity->description());
            getter->setInputs(0);
            getter->setOutputs(1);
            getter->setOutputNames({ "reference" });
            getter->setInstructionId(dnai::enums::QInstructionID::GETTER);
            getter->setConstruction({ entity->id() });

            addItem(getter, returns, entity);

            /*
            * Create contextItem for setter
            */
            ContextMenuItem *setter = new ContextMenuItem();
            setter->setName("Set " + entity->name());
            setter->setDescription(entity->description());
            setter->setInputs(1);
            setter->setInputNames({ "value" });
            setter->setOutputs(1);
            setter->setOutputNames({ "reference" });
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
            getAttributes->setInputs(1);
            getAttributes->setInputNames({"this"});
            getAttributes->setOutputs(data->attributes().count());
            getAttributes->setOutputNames(data->attributes());
            getAttributes->setInstructionId(dnai::enums::QInstructionID::GET_ATTRIBUTES);
            getAttributes->setConstruction({entity->id()});

            addItem(getAttributes, entityCategory, entity);

            /*
             * Set attributes
             */
            ContextMenuItem *setAttributes = new ContextMenuItem();
            setAttributes->setName("Set attributes");
            setAttributes->setDescription("Set attributes of " + entity->name() + " variable");
            setAttributes->setInputs(1 + data->attributes().count());
            setAttributes->setInputNames(QStringList({"this"}) + data->attributes());
            setAttributes->setOutputs(data->attributes().count());
            setAttributes->setOutputNames(data->attributes());
            setAttributes->setFlowIn(1);
            setAttributes->setFlowOut(1);
            setAttributes->setType(entity->entityType());
            setAttributes->setInstructionId(dnai::enums::QInstructionID::SET_ATTRIBUTES);
            setAttributes->setConstruction({entity->id()});

            addItem(setAttributes, entityCategory, entity);
        }

        void ContextMenuModel::appendList(Entity *entity)
        {
            models::ListType *data = entity->guiModel<models::ListType>();
            models::Entity *stored = dnai::gcore::HandlerManager::Instance().getEntity(data->storedType());

            ContextMenuItem *entityCategory = new ContextMenuItem();
            entityCategory->setName(entity->fullName());
            addItem(entityCategory, m_lists, entity);

            /*
             * Foreach
             */
            ContextMenuItem *foreachins = new ContextMenuItem();
            foreachins->setName("Foreach");
            foreachins->setDescription("Iterate over " + entity->name() + " elements");
            foreachins->setInputs(1);
            foreachins->setInputNames({"array"});
            foreachins->setOutputs(2);
            foreachins->setOutputNames({"index", "element"});
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
            insertins->setInputs(3);
            insertins->setInputNames({"array", "element", "index"});
            insertins->setOutputs(1);
            insertins->setOutputNames({"count"});
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
            appendins->setInputs(2);
            appendins->setInputNames({"array", "element"});
            appendins->setOutputs(1);
            appendins->setOutputNames({"count"});
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
            removeins->setInputs(2);
            removeins->setInputNames({"array", "element"});
            removeins->setOutputs(1);
            removeins->setOutputNames({"removed"});
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
            removeAtins->setInputs(2);
            removeAtins->setInputNames({"array", "index"});
            removeAtins->setOutputs(1);
            removeAtins->setOutputNames({"removed"});
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
            sizeins->setInputs(1);
            sizeins->setInputNames({"array"});
            sizeins->setOutputs(1);
            sizeins->setOutputNames({"count"});
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
            clearins->setInputs(1);
            clearins->setInputNames({"array"});
            clearins->setOutputs(0);
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
            fillins->setInputs(3);
            fillins->setInputNames({"array", "element", "count"});
            fillins->setOutputs(1);
            fillins->setOutputNames({"count"});
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
            setvalueatins->setInputs(3);
            setvalueatins->setInputNames({"array", "value", "index"});
            setvalueatins->setOutputs(1);
            setvalueatins->setOutputNames({"value"});
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
            accessins->setInputs(2);
            accessins->setInputNames({"LeftOperand", "RightOperand"});
            accessins->setOutputs(1);
            accessins->setOutputNames({"result"});
            accessins->setType(entity->entityType());
            accessins->setInstructionId(dnai::enums::QInstructionID::ACCESS);
            accessins->setConstruction({entity->id(), 2, stored->id()});

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
            logCat->setName(entity->fullName());

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

        void ContextMenuModel::appendFunction(Entity *entity)
        {
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
            callfuncins->setInputs(data->inputs().count());
            QStringList inpNames;

            for (models::Entity *curr : data->inputs())
            {
                inpNames.append(curr->name());
                refreshItems(curr);
            }
            callfuncins->setInputNames(inpNames);

            callfuncins->setOutputs(data->outputs().count());
            QStringList oupNames;

            for (models::Entity *curr : data->outputs())
            {
                oupNames.append(curr->name());
                refreshItems(curr);
            }
            callfuncins->setOutputNames(oupNames);
            callfuncins->setFlowIn(1);
            callfuncins->setFlowOut(1);
            callfuncins->setType(entity->entityType());
            callfuncins->setInstructionId(dnai::enums::QInstructionID::FUNCTION_CALL);
            callfuncins->setConstruction({entity->id()});

            addItem(callfuncins, funcCat, entity);
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

            for (QString const &curr : m_entity_items[related])
            {
                for (models::gui::Instruction *torebuild : dnai::gcore::HandlerManager::Instance().function()->instruction()->getInstructionsOfPath(curr))
                {
                    dnai::gcore::HandlerManager::Instance().function()->rebuildInstruction(torebuild);
                }
            }
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
	}
}
