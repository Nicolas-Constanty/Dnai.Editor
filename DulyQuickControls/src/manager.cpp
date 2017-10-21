#include "manager.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QUrl>

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

    void Manager::loadProject(const QString &path)
    {
        QFile file(QUrl(path).toLocalFile());

        if (!file.open(QIODevice::ReadWrite)) {
            qWarning("Couldn't open file.");
            return;
        }

        QByteArray data = file.readAll();

        QJsonObject obj(QJsonDocument::fromJson(data).object());

        m_project = new Project(obj["name"].toString(), obj["description"].toString(), file);
        m_project->unserialize(obj);
    }
}
