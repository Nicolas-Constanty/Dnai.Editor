#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "project.h"
#include "models/treemodel.h"
#include "models/treeitem.h"
#include "models/user.h"
#include "models/declarationmodel.h"
#include "views/layout.h"
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
	    explicit Manager(QObject *parent = 0);
        virtual ~Manager();

        static const QString project_extension;

    private:
        void createTreeModel(Project *project);
        Project *m_project;
	    void createNameSpaceModel(models::TreeItem *item);

    public:
        Q_INVOKABLE void createProject(const QString &, const QString &, const QString &);
        Q_INVOKABLE QJsonObject loadProjectData(const QString &);
        Q_INVOKABLE void downloadProjectData(uint, const QString &);
        Q_INVOKABLE void openProject(const QString &);
        Q_INVOKABLE void openProject(Project *);
	    Q_INVOKABLE QModelIndex getIndexMatch(dnai::models::TreeItem * md);
	    Q_INVOKABLE QModelIndex getIndexMatchFromModel(dnai::models::Common *md);
	    Q_INVOKABLE void selectTreeItem(const QModelIndex &index);
	    Q_INVOKABLE void updateNamespace(const QModelIndex &index);
	    Q_INVOKABLE void addContext(int index, int listindex) const;
	    Q_INVOKABLE void addClass(int index, int listindex) const;
	    Q_INVOKABLE void addFunction(int index, int listindex) const;
	    Q_INVOKABLE void addVariable(int index, int listindex) const;
	    Q_INVOKABLE void signin(const QString &, const QString &);
        Q_INVOKABLE bool uploadFile(const QString &);
        Q_INVOKABLE void updateCurentUserFiles();
	    Q_INVOKABLE void logout();
	    Q_INVOKABLE void setAppViewLayout(dnai::views::Layout* l) const;
		Q_INVOKABLE void registerTreeView(QQuickItem *tr);
		Q_INVOKABLE QQuickItem *treeView() const;

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
	    void setDeclarationModel(models::DeclarationModel * m);
	    models::DeclarationModel * declarationModel() const { return m_declRef; }
	    models::User *user() const;
	    void setUser(models::User *user);

    private:
	    Project *loadProject(const QString &);
        Project *loadProject(const QJsonObject &, QFile &);
	    models::TreeModel *m_projectModel;
	    QVariant m_namespacebarmodel;
	    models::TreeItem *m_currentPath;
	    QVariant m_declarationModel;
	    models::DeclarationModel *m_declRef;
		QQuickItem* m_treeView;

	    void setupClassModel(models::Class *cl, int level) const;
	    void setupFunctionModel(models::Function *func) const;
	    void setupContextModel(models::Context *context, int level) const;
	    void setupVariableModel(models::Variable *variable) const;
	    void createDeclarationModel(Project *project) const;
	    void clearDeclarationModel() const;
	    void createDeclarationIfMissing(models::Common *c) const;
		static void createDeclarationView();
		void createNameSpaceView() const;
	    static void createInstructionView();
	    models::User *m_user;
    };
    }

#endif // MANAGER_H
