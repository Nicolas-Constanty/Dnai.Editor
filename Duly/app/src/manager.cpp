#include "manager.h"
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QUrl>
#include "dulyapp.h"
#include "views/declarationcanvas.h"
#include "models/treeitem.h"
#include "models/imodel.h"

namespace duly_gui {
    const QString Manager::project_extension = ".dulyproject";

    Manager::Manager(QObject *parent): QObject(parent)
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

    void Manager::openProject(const QString &path)
    {
        this->openProject(this->loadProject(path));
    }

    void Manager::openProject(Project *project)
    {
        DulyApp::currentCanvasInstance()->resetContent();
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
        DulyApp::currentCanvasInstance()->resetContent();
        models::IModel *model = m_currentPath->model();
        if (dynamic_cast<models::Context*>(model))
        {
            views::DeclarationCanvas::CreateContext(static_cast<models::Context*>(static_cast<models::Common*>(model)), true);
        }
        if (dynamic_cast<models::Class*>(model))
        {
            views::DeclarationCanvas::CreateClass(static_cast<models::Class*>(static_cast<models::Common*>(model)), true);
        }
    }

    void Manager::selectTreeItem(const QModelIndex &index)
    {
        m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
        createNameSpaceModel(m_currentPath);
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

        auto ns = new models::NameSpaceBarItem();
        ns->setPath(item->data(0).toString());
        ns->setAsChild(item->childCount());
        ns->setIdx(item->idxmodel());
        ns->setModel(item->model());
        temp.append(ns);
        while (item->parentItem()->parentItem())
        {
            item = item->parentItem();
            ns = new models::NameSpaceBarItem();
            ns->setPath(item->data(0).toString());
            ns->setAsChild(item->childCount());
            temp.append(ns);
        }
        std::reverse(temp.begin(), temp.end());
        setNamespacebarModel(QVariant::fromValue(temp));
    }
}
