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

    models::Variable *Project::createVariable(const QJsonObject &obj)
    {
        auto model = new models::Variable(
                    obj["name"].toString(),
                    obj["description"].toString(),
                    obj["type"].toString(),
                    obj["internal"].toBool()
                );

        return model;
    }
    models::Input *Project::createInput(const QJsonObject &obj)
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
    models::Output *Project::createOutput(const QJsonObject &obj)
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
    models::Flow *Project::createFlow(const QJsonObject &obj)
    {
        auto model = new models::Flow(
                    obj["uid"].toString(),
                    obj["linked_uid"].toString()
                );

        return model;
    }
    models::Function *Project::createFunction(const QJsonObject &obj, models::Context *parent)
    {
        auto model = new models::Function(obj["name"].toString(), obj["description"].toString(), parent);

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->createVariable(variable.toObject()));
        }

        foreach (auto input, obj["inputs"].toArray()) {
            model->inputs().append(this->createInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->outputs().append(this->createOutput(output.toObject()));
        }

        foreach (auto node, obj["nodes"].toArray()) {
            model->nodes().append(this->createNode(node.toObject(), model));
        }

        m_functions.append(model);

        return model;
    }
    models::Class *Project::createClass(const QJsonObject &obj, models::Context *parent)
    {
        Q_UNUSED(parent);
        //TODO parent for class
        auto model = new models::Class(obj["name"].toString(), obj["description"].toString());

        foreach (auto attribute, obj["attributes"].toArray()) {
            model->attributes().append(this->createVariable(attribute.toObject()));
        }

        foreach (auto method, obj["methods"].toArray()) {
            model->methods().append(this->createFunction(method.toObject(), nullptr));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->createVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->createFunction(function.toObject(), nullptr));
        }

        m_index.append(model);

        return model;
    }
    models::Context *Project::createContext(const QJsonObject &obj, models::Context *parent)
    {
        auto model = new models::Context(obj["name"].toString(), obj["description"].toString());

        foreach (auto context, obj["contexts"].toArray()) {
            model->contexts().append(this->createContext(context.toObject(), model));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->createVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->createFunction(function.toObject(), model));
        }

        m_index.append(model);

        return model;
    }
    models::Node *Project::createNode(const QJsonObject &obj, models::Function *parent)
    {
        auto position = obj["position"].toObject();
        auto model = new models::Node(
                    obj["name"].toString(),
                obj["description"].toString(),
                QVector2D(position["x"].toDouble(), position["y"].toDouble()), parent);
        //model->setFunction(); //TODO find function

        foreach (auto input, obj["inputs"].toArray()) {
            model->inputs().append(this->createInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->outputs().append(this->createOutput(output.toObject()));
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
            m_nodes.append(this->createNode(node.toObject(), nullptr));
        }

        foreach (auto context, obj["contexts"].toArray()) {
            m_contexts.append(this->createContext(context.toObject(), nullptr));
        }
    }
}
