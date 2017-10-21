#include <QJsonDocument>
#include <QJsonArray>
#include "project.h"

namespace duly_gui {
    Project::Project(QString const &name, QString const &description, QFile &file)
        : models::Common(name, description), m_file(file)
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

    QFile &Project::file() const
    {
        return m_file;
    }

    models::Variable *Project::unserializeVariable(const QJsonObject &obj)
    {
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
        auto model = new models::Flow(
                    obj["uid"].toString(),
                    obj["linked_uid"].toString()
                );

        return model;
    }
    models::Function *Project::unserializeFunction(const QJsonObject &obj, models::Context *parent)
    {
        auto model = new models::Function(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto input, obj["inputs"].toArray()) {
            model->inputs().append(this->unserializeInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->outputs().append(this->unserializeOutput(output.toObject()));
        }

        foreach (auto node, obj["nodes"].toArray()) {
            model->nodes().append(this->unserializeNode(node.toObject(), model));
        }

        m_functions_index.append(model);

        return model;
    }
    models::Class *Project::unserializeClass(const QJsonObject &obj, models::Context *parent)
    {
        //TODO parent for class childs
        auto model = new models::Class(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto attribute, obj["attributes"].toArray()) {
            model->attributes().append(this->unserializeVariable(attribute.toObject()));
        }

        foreach (auto method, obj["methods"].toArray()) {
            model->methods().append(this->unserializeFunction(method.toObject(), nullptr));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->unserializeFunction(function.toObject(), nullptr));
        }

        m_index.append(model);

        return model;
    }
    models::Context *Project::unserializeContext(const QJsonObject &obj, models::Context *parent)
    {
        auto model = new models::Context(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto context, obj["contexts"].toArray()) {
            model->contexts().append(this->unserializeContext(context.toObject(), model));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->unserializeVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->unserializeFunction(function.toObject(), model));
        }

        m_index.append(model);

        return model;
    }
    models::Node *Project::unserializeNode(const QJsonObject &obj, models::Function *parent)
    {
        auto position = obj["position"].toObject();
        auto model = new models::Node(
                    obj["name"].toString(),
                obj["description"].toString(),
                QVector2D(static_cast<float>(position["x"].toDouble()), static_cast<float>(position["y"].toDouble())),
                parent);
        //model->setFunction(); //TODO find function

        foreach (auto input, obj["inputs"].toArray()) {
            model->inputs().append(this->unserializeInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->outputs().append(this->unserializeOutput(output.toObject()));
        }

        m_index.append(model);

        return model;
    }

    void Project::serialize(QJsonObject &obj) const
    {
        models::Common::serialize(obj);

        QJsonArray contexts;
        foreach (const models::Context *context, m_contexts) {
            QJsonObject var;
            context->serialize(var);
            contexts.append(var);
        }

        QJsonArray nodes;
        foreach (const models::Node *node, m_nodes) {
            QJsonObject var;
            node->serialize(var);
            nodes.append(var);
        }

        obj["contexts"] = contexts;
        obj["nodes"] = nodes;
    }

    void Project::unserialize(const QJsonObject &obj)
    {
        foreach (auto node, obj["nodes"].toArray()) {
            m_nodes.append(this->unserializeNode(node.toObject(), nullptr));
        }

        foreach (auto context, obj["contexts"].toArray()) {
            m_contexts.append(this->unserializeContext(context.toObject(), nullptr));
        }
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
