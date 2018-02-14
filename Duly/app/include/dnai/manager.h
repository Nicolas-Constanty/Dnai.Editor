#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
#include "models/treemodel.h"
#include "models/namespacebarmodel.h"
#include "models/treeitem.h"
#include "models/user.h"
#include "models/declarationmodel.h"
#include "api.h"

namespace dnai {
    class Manager: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(dnai::models::TreeModel *projectModel READ projectModel WRITE setProjectModel NOTIFY projectModelChanged)
        Q_PROPERTY(QVariant namespacebarModel READ namespacebarModel WRITE setNamespacebarModel NOTIFY namespacebarModelChanged)
        Q_PROPERTY(dnai::models::DeclarationModel *declarationModel READ declarationModel WRITE setDeclarationModel NOTIFY declarationModelChanged)
        Q_PROPERTY(dnai::models::User *user READ user WRITE setUser NOTIFY userChanged)

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
        Q_INVOKABLE QModelIndex getIndexMatch(dnai::models::TreeItem *index);
        Q_INVOKABLE QModelIndex getIndexMatchFromModel(dnai::models::Common *md);
        Q_INVOKABLE void selectTreeItem(const QModelIndex &index);
        Q_INVOKABLE void updateNamespace(const QModelIndex &index);
        Q_INVOKABLE void addContext(int index, int listindex);
        Q_INVOKABLE void addClass(int index, int listindex);
        Q_INVOKABLE void addFunction(int index, int listindex);
        Q_INVOKABLE void addVariable(int index, int listindex);

        Q_INVOKABLE void signin(const QString &, const QString &);
        Q_INVOKABLE void logout();

    signals:
        void projectModelChanged(models::TreeModel *model);
        void namespacebarModelChanged(const QVariant  &ref);
        void declarationModelChanged(models::DeclarationModel *ref);
        void userChanged(models::User *user);

    public:
        models::TreeModel *projectModel() const { return m_projectModel; }
        void setProjectModel(models::TreeModel *model);
        QVariant namespacebarModel() const { return m_namespacebarmodel; }
        void setNamespacebarModel(const QVariant &ref);
        void setDeclarationModel(models::DeclarationModel *ref);
        models::DeclarationModel * declarationModel() const { return m_declRef; }
        models::User *user() const;
        void setUser(models::User *user);

    private:
         Project *loadProject(const QString &);
         models::TreeModel *m_projectModel;
         QVariant m_namespacebarmodel;
         models::TreeItem *m_currentPath;
         QVariant m_declarationModel;
         models::DeclarationModel *m_declRef;
         void setupClassModel(models::Class *cl, int level);
         void setupFunctionModel(models::Function *func);
         void setupContextModel(models::Context *context, int level);
         void setupVariableModel(models::Variable *variable);
         void createDeclarationModel(Project *project);
         void clearDeclarationModel();
         void createDeclarationIfMissing(models::Common *c);
         models::User *m_user;
    };
}

#endif // MANAGER_H
