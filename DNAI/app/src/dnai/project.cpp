#include <QJsonDocument>
#include <QJsonArray>

#include "dnai/project.h"

namespace dnai {
//    Project::Project(const qint32 uid, QString const &name, QString const &description, QFile &file)
//        : models::Common(uid, name, description, 0, 0), m_file(file),
//          m_main(new models::Context(-1,"DNAI", "main", QVector2D(), 0, 0))
//    {

//    }

//    Project::Project(QString const &name, QString const &description, QFile &file)
//        : models::Common(-2, name, description, 0, 0), m_file(file),
//          m_main(new models::Context(-1,"DNAI", "main", QVector2D(), 0, 0))
//    {

//    }

//    Project::~Project()
//    {

//    }

//    void    Project::save()
//    {
//        QJsonObject obj;
//        serialize(obj);

//        m_file.write(QJsonDocument(obj).toJson());
//    }

//    const models::Context *Project::main() const
//    {
//        return m_main;
//    }

//    QJsonObject Project::data() const
//    {
//        return QJsonObject {
//            {"name", name()},
//            {"description", description()},
//            {"count", QJsonObject {
//                    {"contexts", count.contexts},
//                    {"classes", count.classes},
//                    {"nodes", count.nodes},
//                    {"functions", count.functions},
//                    {"variables", count.variables},
//                    {"inputs", count.inputs},
//                    {"outputs", count.outputs},
//                    {"flows", count.flows}
//                }
//            }
//        };
//    }

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
