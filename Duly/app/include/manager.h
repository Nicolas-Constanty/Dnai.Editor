#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
#include "models/treemodel.h"
#include "models/namespacebarmodel.h"

namespace duly_gui {
    class Manager: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(duly_gui::models::TreeModel *projectModel READ projectModel WRITE setProjectModel NOTIFY projectModelChanged)
        Q_PROPERTY(QVariant namespacebarModel READ namespacebarModel WRITE setNamespacebarModel NOTIFY namespacebarModelChanged)
    public:
        Manager(QObject *parent = 0);
        virtual ~Manager();

        static const QString project_extension;

    private:
        void createTreeModel(Project *project);
        Project *m_project;
        void createNameSpaceModel(models::TreeItem *item);

    public:
        Q_INVOKABLE void createProject(const QString &, const QString &, const QString &);
        Q_INVOKABLE QJsonObject loadProjectData(const QString &);
        Q_INVOKABLE void openProject(const QString &);
        Q_INVOKABLE void openProject(Project *);
        Q_INVOKABLE void updateNamespace(const QModelIndex &index);
        Q_INVOKABLE void selectTreeItem(const QModelIndex &index);

    signals:
        void projectModelChanged(models::TreeModel *model);
        void namespacebarModelChanged(const QVariant  &ref);

    public:
        models::TreeModel *projectModel() const { return m_projectModel; }
        void setProjectModel(models::TreeModel *model);
        QVariant namespacebarModel() const { return m_namespacebarmodel; }
        void setNamespacebarModel(const QVariant &ref);

    private:
         Project *loadProject(const QString &);
         models::TreeModel *m_projectModel;
         QVariant m_namespacebarmodel;
         models::TreeItem *m_currentPath;
    };
}

#endif // MANAGER_H
