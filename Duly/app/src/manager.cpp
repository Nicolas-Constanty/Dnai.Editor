#include "manager.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include "dulyapp.h"
#include "views/declarationcanvas.h"

namespace duly_gui {
    const QString Manager::project_extension = ".dulyproject";

    Manager::Manager(QObject *parent): QObject(parent)
    {

    }

    Manager::~Manager()
    {

    }

    void Manager::createProject(const QString &name, const QString &description, const QString &path)
    {
        auto fileUrl = QUrl(QDir(path).filePath(name) + project_extension);
        QFile file(fileUrl.toLocalFile());
        if (!file.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open file.");
            qDebug() << file.errorString();
            return;
        }

        m_project = new Project(name, description, file);
        m_project->save();
    }

    QJsonObject Manager::loadProjectData(const QString &path)
    {
        Project *project = this->loadProject(path);
        return (project != nullptr) ? project->data() : QJsonObject {};
    }

    Project * Manager::loadProject(const QString &path)
    {
        QFile file(QUrl(path).toLocalFile());

        if (!file.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open file.");
            return nullptr;
        }

        QByteArray data = file.readAll();

        QJsonObject obj(QJsonDocument::fromJson(data).object());

        Project *project = new Project(obj["name"].toString(), obj["description"].toString(), file);
        project->unserialize(obj);
        return project;
    }

    void Manager::openProject(const QString &path)
    {
        m_project = this->loadProject(path);
		views::DeclarationCanvas::CreateContext(m_project->main(), true);
    }

    void Manager::openProject(Project *project)
    {
        m_project = project;
    }
}
