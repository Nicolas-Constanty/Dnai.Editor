#include "manager.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include "dulyapp.h"
#include "views/declarationcanvas.h"
#include "models/treeitem.h"

namespace duly_gui {
    const QString Manager::project_extension = ".dulyproject";

    Manager::Manager(QObject *parent): QObject(parent), m_user(nullptr)
    {
        m_projectModel = nullptr;
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
    
    models::User *Manager::user() const
    {
        return m_user;
    }
    
    void Manager::setUser(models::User *user)
    {
        m_user = user;
    }
    
    void Manager::openProject(const QString &path)
    {
        this->openProject(this->loadProject(path));
    }
    
    void Manager::openProject(Project *project)
    {
        m_project = project;
        m_project->declare();
        createTreeModel(m_project);
        m_currentPath = static_cast<models::TreeItem*>(m_projectModel->index(0,0).internalPointer());
        createNameSpaceModel(m_currentPath);
        views::DeclarationCanvas::CreateContext(m_project->main(), true);
    }

    void Manager::updateNamespace(const QModelIndex &index)
    {
        m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
        createNameSpaceModel(m_currentPath);
    }

    void Manager::selectTreeItem(const QModelIndex &index)
    {
        m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
        createNameSpaceModel(m_currentPath);
    }

    void Manager::signin(const QString &username, const QString &password)
    {
        // TODO get user from API
        api::signin(username, password).map(nullptr, [this](Response response) -> Response {
            m_user = new models::User();
            m_user->setName("John Doe");
            m_user->setProfile_url("../Images/default_user.png");
            emit userChanged(m_user);
            return response;
        });
    }

    void Manager::logout()
    {
        api::logout();
        delete m_user;
        m_user = nullptr;
    }

    void Manager::setProjectModel(models::TreeModel *model)
    {
        if (model == nullptr || m_projectModel == model)
            return;
        m_projectModel = model;
        emit projectModelChanged(model);
    }

    void Manager::setNamespacebarModel(const QVariant &ref)
    {
        m_namespacebarmodel = ref;
        emit namespacebarModelChanged(ref);
    }

    void Manager::createTreeModel(Project *project)
    {
        setProjectModel(new models::TreeModel(project));
    }

    void Manager::createNameSpaceModel(models::TreeItem *item)
    {
        QList<QObject *> temp;

        auto ns = new NameSpaceBarItem();
        ns->setPath(item->data(0).toString());
        ns->setAsChild(item->childCount());
        ns->setIdx(item->idxmodel());
        temp.append(ns);
        while (item->parentItem()->parentItem())
        {
            item = item->parentItem();
            ns = new NameSpaceBarItem();
            ns->setPath(item->data(0).toString());
            ns->setAsChild(item->childCount());
            temp.append(ns);
        }
        std::reverse(temp.begin(), temp.end());
        setNamespacebarModel(QVariant::fromValue(temp));
    }
}
