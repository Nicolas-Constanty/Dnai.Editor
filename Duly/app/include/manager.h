#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
#include "models/treemodel.h"

namespace duly_gui {
    class Manager: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(models::TreeModel *projectModel READ projectModel WRITE setProjectModel NOTIFY projectModelChanged)
    public:
        Manager(QObject *parent = 0);
        virtual ~Manager();

        static const QString project_extension;

    private:
        void createTreeModel(Project *project);
        Project *m_project;

    public:
        Q_INVOKABLE void createProject(const QString &, const QString &, const QString &);
        Q_INVOKABLE QJsonObject loadProjectData(const QString &);
        Q_INVOKABLE void openProject(const QString &);
        Q_INVOKABLE void openProject(Project *);

    signals:
        void projectModelChanged(const models::TreeModel *model);

    public:
        models::TreeModel *projectModel() const { return m_projectModel; }
        void setProjectModel(models::TreeModel *model);
    private:
         Project *loadProject(const QString &);
         models::TreeModel *m_projectModel;
    };
}

#endif // MANAGER_H
