#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
#include "models/treemodel.h"
#include "models/namespacebarmodel.h"
#include "models/user.h"
#include "api.h"

namespace duly_gui {
    class Manager: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(duly_gui::models::TreeModel *projectModel READ projectModel WRITE setProjectModel NOTIFY projectModelChanged)
        Q_PROPERTY(QVariant namespacebarModel READ namespacebarModel WRITE setNamespacebarModel NOTIFY namespacebarModelChanged)
        Q_PROPERTY(duly_gui::models::User *user READ user WRITE setUser NOTIFY userChanged)

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

        Q_INVOKABLE void signin(const QString &, const QString &);
        Q_INVOKABLE void logout();

    signals:
        void projectModelChanged(models::TreeModel *model);
        void namespacebarModelChanged(const QVariant  &ref);
        void userChanged(models::User *user);

    public:
        models::TreeModel *projectModel() const { return m_projectModel; }
        void setProjectModel(models::TreeModel *model);
        QVariant namespacebarModel() const { return m_namespacebarmodel; }
        void setNamespacebarModel(const QVariant &ref);

        models::User *user() const;
        void setUser(models::User *user);

    private:
        Project *loadProject(const QString &);
        models::TreeModel *m_projectModel;
         QVariant m_namespacebarmodel;
         models::TreeItem *m_currentPath;
         models::User *m_user;
    };
}

#endif // MANAGER_H
