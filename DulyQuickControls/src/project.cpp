#include "project.h"
#include <QJsonObject>
#include <QJsonArray>

namespace duly_gui {
    Project::Project(QString const &name, QString const &path): m_name(name), m_path(path)
    {

    }

    Project::~Project()
    {

    }

    void    Project::save()
    {

    }

    const QString &Project::path() const
    {
        return m_path;
    }

    void Project::setPath(const QString &path)
    {
        m_path = path;
    }

    const QString &Project::name() const
    {
        return m_name;
    }

    void Project::setName(const QString &name)
    {
        m_name = name;
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
    models::Function *Project::createFunction(const QJsonObject &obj)
    {
        auto model = new models::Function(obj["name"].toString(), obj["description"].toString());

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
            model->nodes().append(this->createNode(node.toObject()));
        }

        return model;
    }
    models::Class *Project::createClass(const QJsonObject &obj)
    {
        auto model = new models::Class(obj["name"].toString(), obj["description"].toString());

        foreach (auto attribute, obj["attributes"].toArray()) {
            model->attributes().append(this->createVariable(attribute.toObject()));
        }

        foreach (auto method, obj["methods"].toArray()) {
            model->methods().append(this->createFunction(method.toObject()));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->createVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->createFunction(function.toObject()));
        }

        return model;
    }
    models::Context *Project::createContext(const QJsonObject &obj)
    {
        auto model = new models::Context(obj["name"].toString(), obj["description"].toString());

        foreach (auto contexte, obj["contexts"].toArray()) {
            model->contexts().append(this->createContext(contexte.toObject()));
        }

        foreach (auto variable, obj["variables"].toArray()) {
            model->variables().append(this->createVariable(variable.toObject()));
        }

        foreach (auto function, obj["functions"].toArray()) {
            model->functions().append(this->createFunction(function.toObject()));
        }

        return model;
    }
    models::Node *Project::createNode(const QJsonObject &obj)
    {
        auto position = obj["position"].toObject();
        auto model = new models::Node(
                    obj["name"].toString(),
                obj["description"].toString(),
                QVector2D(position["x"].toDouble(), position["y"].toDouble()));
        //model->setContext(); //TODO find context
        //model->setFunction(); //TODO find function

        foreach (auto input, obj["inputs"].toArray()) {
            model->inputs().append(this->createInput(input.toObject()));
        }

        foreach (auto output, obj["outputs"].toArray()) {
            model->outputs().append(this->createOutput(output.toObject()));
        }

        return model;
    }

}
