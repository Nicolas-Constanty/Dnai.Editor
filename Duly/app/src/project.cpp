#include <QJsonDocument>
#include <QJsonArray>
#include "project.h"

namespace duly_gui {
    Project::Project(QString const &name, QString const &description, QFile &file)
        : models::Common(name, description), m_file(file), m_main(new models::Context("Duly", "main"))
    {
    }

    Project::~Project()
    {

    }

    void    Project::save()
    {
        QJsonObject obj;
        serialize(obj);

        m_file.write(QJsonDocument(obj).toJson());
    }

    const models::Context *Project::main() const
    {
        return m_main;
    }

    QJsonObject Project::data() const
    {
        return QJsonObject {
            {"name", name()},
            {"description", description()},
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
        };
    }

    QFile &Project::file() const
    {
        return m_file;
    }

    models::Variable *Project::unserializeVariable(const QJsonObject &obj)
    {
        ++count.variables;
        auto model = new models::Variable(
                    obj["name"].toString(),
                    obj["description"].toString(),
                    obj["type"].toString(),
                    obj["internal"].toBool()
                );

        return model;
    }
    models::Input *Project::unserializeInput(const QJsonObject &obj)
    {
        ++count.inputs;
        auto model = new models::Input(
                    obj["name"].toString(),
                    obj["description"].toString(),
                    obj["type"].toString(),
                    obj["internal"].toBool(),
                    obj["uid"].toString(),
                    obj["linked_uid"].toString()
                );

        return model;
    }
    models::Output *Project::unserializeOutput(const QJsonObject &obj)
    {
        ++count.outputs;
        auto model = new models::Output(
                    obj["name"].toString(),
                    obj["description"].toString(),
                    obj["type"].toString(),
                    obj["internal"].toBool(),
                    obj["uid"].toString(),
                    obj["linked_uid"].toString()
                );

        return model;
    }
    models::Flow *Project::unserializeFlow(const QJsonObject &obj)
    {
        ++count.flows;
        auto model = new models::Flow(
                    obj["uid"].toString(),
                    obj["linked_uid"].toString()
                );

        return model;
    }
    models::Function *Project::unserializeFunction(const QJsonObject &obj, models::Context *parent)
    {
        ++count.functions;
        auto model = new models::Function(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto variable, obj["variables"].toArray()) {
            model->addVariable(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto input, obj["inputs"].toArray()) {
            model->addInput(this->unserializeInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->addOutput(this->unserializeOutput(output.toObject()));
        }

        foreach (auto node, obj["nodes"].toArray()) {
            model->addNode(this->unserializeNode(node.toObject(), model));
        }

        m_functions_index.append(model);
        m_index.append(model);

        return model;
    }
    models::Class *Project::unserializeClass(const QJsonObject &obj, models::Context *parent)
    {
        ++count.classes;
        //TODO parent for class childs
        auto model = new models::Class(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto attribute, obj["attributes"].toArray()) {
            model->addAttribute(this->unserializeVariable(attribute.toObject()));
        }

        foreach (auto method, obj["methods"].toArray()) {
            model->addMethod(this->unserializeFunction(method.toObject(), nullptr));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->addVariable(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->addFunction(this->unserializeFunction(function.toObject(), nullptr));
        }

        m_index.append(model);

        return model;
    }
    models::Context *Project::unserializeContext(const QJsonObject &obj, models::Context *parent)
    {
        ++count.contexts;
        auto model = new models::Context(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto context, obj["contexts"].toArray()) {
            model->addContext(this->unserializeContext(context.toObject(), model));
        }

        foreach (auto classe, obj["classes"].toArray()) {
            model->addClass(this->unserializeClass(classe.toObject(), model));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->addVariable(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->addFunction(this->unserializeFunction(function.toObject(), model));
        }

        m_index.append(model);

        return model;
    }
    models::Node *Project::unserializeNode(const QJsonObject &obj, models::Function *parent)
    {
        ++count.nodes;
        auto position = obj["position"].toObject();
        auto model = new models::Node(
                    obj["name"].toString(),
                obj["description"].toString(),
                QVector2D(static_cast<float>(position["x"].toDouble()), static_cast<float>(position["y"].toDouble())),
                parent);

        auto functions_found = this->searchFunctions(obj["function"].toString(), [] (models::Function *model, QString const &search) -> bool {
            return model->name() == search;
        });

        model->setFunction(functions_found.first());

        foreach (auto input, obj["inputs"].toArray()) {
            model->addInput(this->unserializeInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->addOutput(this->unserializeOutput(output.toObject()));
        }

        foreach (auto flow_in, obj["flows_in"].toArray()) {
            model->addFlowIn(this->unserializeFlow(flow_in.toObject()));
        }

        foreach (auto flow_out, obj["flows_out"].toArray()) {
            model->addFlowOut(this->unserializeFlow(flow_out.toObject()));
        }

        m_index.append(model);

        return model;
    }

    void Project::serialize(QJsonObject &obj) const
    {
        models::Common::serialize(obj);
        QJsonObject main;
        m_main->serialize(main);
        obj["main"] = main;
    }

    void Project::unserialize(const QJsonObject &obj)
    {
        m_main = this->unserializeContext(obj["main"].toObject(), nullptr);
    }

    QVector<models::Common *> Project::search(const QString &search, searchFunc func)
    {
        QVector<models::Common *> models;

        foreach (auto model, m_index) {
            if (func(model, search)) {
                models.append(model);
            }
        }

        return models;
    }

    QVector<models::Function *> Project::searchFunctions(const QString &search, searchFunctionsFunc func)
    {
        QVector<models::Function *> models;

        foreach (auto model, m_functions_index) {
            if (func(model, search)) {
                models.append(model);
            }
        }

        return models;
    }

    bool Project::defaultSearchFunc(models::Common *model, const QString &search)
    {
        return model->name().startsWith(search);
    }

    bool Project::defaultSearchFunctionsFunc(models::Function *model, const QString &search)
    {
        return model->name().startsWith(search);
    }
}
