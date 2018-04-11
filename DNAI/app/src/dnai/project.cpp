#include <QJsonDocument>

#include "dnai/project.h"
#include "dnai/models/gui/declarable/context.h"
#include "dnai/exceptions/guiexception.h"
#include "dnai/exceptions/exceptionmanager.h"
#include "dnai/editor.h"

namespace dnai {
	Project::Project(): EntityTree(nullptr), m_file(nullptr), m_selectedEntity(nullptr), m_rootEntity(nullptr)
	{
	}

    Project::~Project()
    {
        delete m_rootEntity;
        qDebug() << "~ Project";
    }

    void Project::save()
    {
        QJsonObject obj;
        serialize(obj);

		m_file->open(QIODevice::WriteOnly);
        m_file->write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
		m_file->close();
    }

	void Project::serialize(QJsonObject &obj) const
	{
        obj["version"] = Editor::instance().version();
		m_rootEntity->serialize(obj);
	}

	void Project::_deserialize(const QJsonObject& obj)
    {
        if (obj["version"].toString() != Editor::instance().version())
            qWarning() << "Warning this project file (" << m_filename << ") wasn't created with the same editor's version (" << obj["version"].toString() << "!= current" << Editor::instance().version() << ")";
        const auto coreModel = new models::core::Entity(obj["name"].toString(), enums::core::ENTITY::CONTEXT);
        m_rootItem = new models::Entity();
        m_rootItem->setIdx(index(0,0, QModelIndex()));
        m_rootEntity = models::Entity::deserialize(obj, coreModel, m_rootItem);
        m_rootEntity->setIsRoot(true);
        m_rootItem->appendChild(m_rootEntity);
    }

	models::Entity* Project::selectedEntity() const
	{
		return m_selectedEntity;
	}

	void Project::setSelectedEntity(models::Entity* entity)
	{
		if (m_selectedEntity == entity)
			return;
		m_selectedEntity = entity;
		emit selectedEntityChanged(entity);
	}

	void Project::load(const QString& path)
	{
		m_filename = path;
		m_file = new QFile(QUrl(m_filename).toLocalFile());

		if (!m_file->open(QIODevice::ReadOnly)) {
			qWarning("Couldn't open file.");
			return;
		}

		const QByteArray data = m_file->readAll();

		try {
			const QJsonObject obj(QJsonDocument::fromJson(data).object());
			_deserialize(obj);
			m_data = obj;
		}
		catch (std::exception &e) {
			Q_UNUSED(e)
			exceptions::ExceptionManager::throwException(exceptions::GuiExeption("Error : Corrupted file"));
            qWarning("Couldn't parse file.");
		}
		m_file->close();
    }

    void Project::loadFromJson(const QJsonObject &obj)
    {
        _deserialize(obj);
        m_data = obj;
    }

	void Project::close()
	{
	}

	const QString& Project::version() const
	{
		return m_version;
	}

	void Project::setVersion(const QString& version)
	{
		if (version == m_version)
			return;
		m_version = version;
	}

	const QString& Project::name() const
	{
		return m_rootEntity->name();
	}

	void Project::setName(const QString& name)
	{
		m_rootEntity->setName(name);
	}

	const QString& Project::description() const
	{
		return m_description;
	}

	void Project::setDescription(const QString& name)
	{
		if (m_description == name)
			return;
		m_description = name;
	}

	const QString& Project::fileName() const
	{
		return m_filename;
	}

	void Project::setFileName(const QString& name)
	{
		if (m_filename == name)
			return;
		m_filename = name;
	}

	template<>
	inline void Project::_foreachEntity(models::Entity *root, const std::function<void(models::Entity *)> &func) const
	{
        const auto& list = root->childrenItem();
		for (auto item : list)
		{
			if (const auto entity = dynamic_cast<models::Entity*>(item))
			{
				func(entity);
				_foreachEntity(item, func);
			}
		}
	}

	template<>
	int Project::_foreachEntity(models::Entity *root, const std::function<int(models::Entity *)> &func) const
	{
		int total = 0;
        const auto& list = root->childrenItem();
		for (auto item : list)
		{
			if (const auto entity = dynamic_cast<models::Entity*>(item))
			{
				total += func(entity);
				total += _foreachEntity(item, func);
			}
		}
		return total;
	}

	void Project::foreachEntity(const std::function<void(models::Entity *)> &func) const
	{
        const auto list = m_rootEntity->childrenItem();
		for (auto item : list)
		{
			if (const auto entity = dynamic_cast<models::Entity*>(item))
			{
				func(entity);
				_foreachEntity(item, func);
			}
		}
	}

	int Project::expandedRows(const QModelIndex &parent) const
	{
		const auto item = getItem(parent);
		const auto count = _foreachEntity<int>(item, [](models::Entity *e)
		{
			if (e->expanded())
				return e->childCount();
			return 0;
		});
		return count + (item->expanded() ? item->childCount() : 0);
    }

    void Project::addClass(int index, const QString & listindex, const QModelIndex &parent)
	{
        models::Entity *parentItem = getItem(parent);
		beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
		parentItem->addClass(index, listindex);
		endInsertRows();
	}

    void Project::addContext(int index, const QString & listindex, const QModelIndex &parent)
	{
        models::Entity *parentItem = getItem(parent);
		beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
		parentItem->addContext(index, listindex);
		endInsertRows();
	}

    void Project::addFunction(int index, const QString & listindex, const QModelIndex &parent)
	{
        models::Entity *parentItem = getItem(parent);
		beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
		parentItem->addFunction(index, listindex);
		endInsertRows();
	}

    void Project::addVariable(int index, const QString & listindex, const QModelIndex &parent)
	{
        models::Entity *parentItem = getItem(parent);
		beginInsertRows(parent, parentItem->childCount(), parentItem->childCount());
		parentItem->addVariable(index, listindex);
		endInsertRows();
	}

	void Project::removeEntity(const QModelIndex &index, models::Entity *e)
	{
		models::Entity *parentItem = getItem(index);
		auto count = 0;
		QModelIndex mi;
		for (auto i : parentItem->childrenItem())
		{
			if (i == e)
            {
                mi = index.child(count, 0);
				break;
			}
			++count;
        }
        beginRemoveRows(index, count, count);
		e->remove();
		endRemoveRows();
	}

	int Project::childCount() const
	{
		return m_rootEntity->childCount();
	}

    models::Entity &Project::getRoot() const
    {
        return *m_rootEntity;
    }

    const QJsonObject &Project::jsonData() const
    {
       /* const auto rootentity = static_cast<models::Entity *>(m_rootItem->child(0));
        return QJsonObject  {
            {"name", rootentity->coreModel()->name() },
            {"description", rootentity->guiModel()->description()},
            {"count", QJsonObject {
                    {"contexts", count.contexts},
                    {"classes", count.classes},
                    {"nodes", count.nodes},
                    {"functions", count.functions},
                    {"variables", count.variables},
                    {"inputs", count.inputs},
                    {"outputs", count.outputs},
                    {"flows", count.flows}
                }
            }
        };*/
		return m_data;
    }

//	QJsonObject Project::loadProjectData(const QString &path)
//	{
//		Project *project = Project::loadProject(path);
//		return (project != nullptr) ? project->data() : QJsonObject{};
//	}

//	Project * Project::loadProject(const QString &path)
//	{
//		QFile file(QUrl(path).toLocalFile());

//		if (!file.open(QIODevice::ReadWrite)) {
//			qWarning("Couldn't open file.");
//			return nullptr;
//		}

//		const QByteArray data = file.readAll();

//		try {
//			const QJsonObject obj(QJsonDocument::fromJson(data).object());
//			return loadProject(obj, file);
//		}
//		catch (std::exception) {

//		}
//		qWarning("Couldn't parse file.");
//		return nullptr;
//	}

//	Project *Project::loadProject(const QJsonObject &obj, QFile &file)
//	{
//		auto project = new Project(obj["name"].toString(), obj["description"].toString(), file);
//		project->unserialize(obj);
//		return project;
//	}

//	QFile &Project::file() const
//    {
//        return m_file;
//    }

//    models::Variable *Project::unserializeVariable(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.variables;
//	    const auto model = new models::Variable(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    unserializePosition(obj["position"].toObject()),
//                    obj["type"].toString(),
//                    obj["internal"].toBool(),
//                    obj["index"].toInt(),
//                    obj["listIndex"].toInt(),
//                    parent
//                );

//        return model;
//    }
//    models::Input *Project::unserializeInput(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.inputs;
//        auto model = new models::Input(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    obj["type"].toString(),
//                    obj["internal"].toBool(),
//                    obj["linked_uid"].toString(),
//                    parent
//                );

//        return model;
//    }
//    models::Output *Project::unserializeOutput(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.outputs;
//        auto model = new models::Output(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    obj["type"].toString(),
//                    obj["internal"].toBool(),
//                    obj["linked_uid"].toString(),
//                    parent
//                );

//        return model;
//    }
//    models::Flow *Project::unserializeFlow(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.flows;
//        auto model = new models::Flow(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    obj["linked_uid"].toString(),
//                    parent
//                );

//        return model;
//    }
//    models::Function *Project::unserializeFunction(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.functions;
//        auto model = new models::Function(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    unserializePosition(obj["position"].toObject()),
//                    obj["index"].toInt(),
//                    obj["listIndex"].toInt(),
//                    parent
//                );

//        foreach (auto variable, obj["variables"].toArray()) {
//            model->addVariable(this->unserializeVariable(variable.toObject(), model));
//        }

//        foreach (auto input, obj["inputs"].toArray()) {
//            model->addInput(this->unserializeInput(input.toObject(), model));
//        }

//        foreach (auto output, obj["outputs"].toArray()) {
//            model->addOutput(this->unserializeOutput(output.toObject(), model));
//        }

//        foreach (auto node, obj["nodes"].toArray()) {
//            model->addNode(this->unserializeNode(node.toObject(), model));
//        }

//        m_functions_index.append(model);
//        m_index.append(model);

//        return model;
//    }
//    models::Class *Project::unserializeClass(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.classes;
//        auto model = new models::Class(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    unserializePosition(obj["position"].toObject()),
//                    obj["index"].toInt(),
//                    obj["listIndex"].toInt(),
//                    parent
//                );

//        foreach (auto attribute, obj["attributes"].toArray()) {
//            model->addAttribute(this->unserializeVariable(attribute.toObject(), model));
//        }

//        foreach (auto method, obj["methods"].toArray()) {
//            model->addMethod(this->unserializeFunction(method.toObject(), model));
//        }

//        foreach (auto classe, obj["classes"].toArray()) {
//            model->addClass(this->unserializeClass(classe.toObject(), model));
//        }

//        foreach (auto function, obj["functions"].toArray()) {
//            model->addFunction(this->unserializeFunction(function.toObject(), model));
//        }

//        m_index.append(model);

//        return model;
//    }
//    models::Context *Project::unserializeContext(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.contexts;
//        auto model = new models::Context(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    unserializePosition(obj["position"].toObject()),
//                    obj["index"].toInt(),
//                    obj["listIndex"].toInt(),
//                    parent
//                );

//        foreach (auto context, obj["contexts"].toArray()) {
//            model->addContext(this->unserializeContext(context.toObject(), model));
//        }

//        foreach (auto classe, obj["classes"].toArray()) {
//            model->addClass(this->unserializeClass(classe.toObject(), model));
//        }

//        foreach (auto variable, obj["variables"].toArray()) {
//            model->addVariable(this->unserializeVariable(variable.toObject(), model));
//        }

//        foreach (auto function, obj["functions"].toArray()) {
//            model->addFunction(this->unserializeFunction(function.toObject(), model));
//        }

//        m_index.append(model);

//        return model;
//    }
//    models::Node *Project::unserializeNode(const QJsonObject &obj, QObject *parent)
//    {
//        ++count.nodes;

//        auto functions_found = this->searchFunctions(obj["function"].toString(), [] (models::Function *model, QString const &search) -> bool {
//            return model->name() == search;
//        });

//        auto model = new models::Node(
//                    obj["uid"].toInt(),
//                    obj["name"].toString(),
//                    obj["description"].toString(),
//                    unserializePosition(obj["position"].toObject()),
//                    functions_found.first(),
//                    parent
//                );

//        foreach (auto input, obj["inputs"].toArray()) {
//            model->addInput(this->unserializeInput(input.toObject(), model));
//        }

//        foreach (auto output, obj["outputs"].toArray()) {
//            model->addOutput(this->unserializeOutput(output.toObject(), model));
//        }

//        foreach (auto flow_in, obj["flows_in"].toArray()) {
//            model->addFlowIn(this->unserializeFlow(flow_in.toObject(), model));
//        }

//        foreach (auto flow_out, obj["flows_out"].toArray()) {
//            model->addFlowOut(this->unserializeFlow(flow_out.toObject(), model));
//        }

//        m_index.append(model);

//        return model;
//    }

//    QVector2D Project::unserializePosition(const QJsonObject &position)
//    {
//        return QVector2D(static_cast<float>(position["x"].toDouble()), static_cast<float>(position["y"].toDouble()));
//    }

//    void Project::serialize(QJsonObject &obj) const
//    {
//        models::Common::serialize(obj);
//        QJsonObject main;
//        m_main->serialize(main);
//        obj["main"] = main;
//    }

//    void Project::declare() const
//    {
//        foreach (auto model, m_index) {
//            model->declare();
//        }
//    }

//    void Project::unserialize(const QJsonObject &obj)
//    {
//        m_main = this->unserializeContext(obj["main"].toObject(), nullptr);
//    }

//    QVector<models::Common *> Project::search(const QString &search, searchFunc func)
//    {
//        QVector<models::Common *> models;

//        foreach (auto model, m_index) {
//            if (func(model, search)) {
//                models.append(model);
//            }
//        }

//        return models;
//    }

//    QVector<models::Function *> Project::searchFunctions(const QString &search, searchFunctionsFunc func)
//    {
//        QVector<models::Function *> models;

//        foreach (auto model, m_functions_index) {
//            if (func(model, search)) {
//                models.append(model);
//            }
//        }

//        return models;
//    }

//    bool Project::defaultSearchFunc(models::Common *model, const QString &search)
//    {
//        return model->name().startsWith(search);
//    }

//    bool Project::defaultSearchFunctionsFunc(models::Function *model, const QString &search)
//    {
//        return model->name().startsWith(search);
//    }
}
