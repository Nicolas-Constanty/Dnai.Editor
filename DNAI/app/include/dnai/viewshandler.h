#ifndef VIEWSHANDLER_H
#define VIEWSHANDLER_H
#include <QQuickItem>

#include "dnai/interfaces/iloadingclass.h"
#include "dnai/models/basicnodemodel.h"
//#include "controllers/propertypanel.h"
//#include "models/property.h"
//#include "models/declarationmodel.h"
#include "dnai/project.h"
//#include "models/treeitem.h"
//#include "models/treemodel.h"

namespace dnai
{
    class ViewsHandler : public QObject, interfaces::ILoadingClass
	{
		Q_OBJECT
//		Q_PROPERTY(dnai::models::TreeModel *projectModel READ projectModel WRITE setProjectModel NOTIFY projectModelChanged)
		Q_PROPERTY(QVariant namespacebarModel READ namespacebarModel WRITE setNamespacebarModel NOTIFY namespacebarModelChanged)
//		Q_PROPERTY(dnai::models::DeclarationModel *declarationModel READ declarationModel WRITE setDeclarationModel NOTIFY declarationModelChanged)
		Q_PROPERTY(dnai::models::BasicNodeModel *basicNodesModel READ basicNodesModel NOTIFY basicNodesModelChanged)
//        Q_PROPERTY(dnai::models::Entity *propertyPanelModel READ propertyPanelModel NOTIFY propertyPanelModelChanged)

	signals:
//		void propertyPanelModelChanged(models::EntityList *) const;
//		void projectModelChanged(models::TreeModel *model);
		void namespacebarModelChanged(const QVariant  &ref);
//		void declarationModelChanged(models::DeclarationModel *ref);
		void basicNodesModelChanged(models::BasicNodeModel *);

	public:
		ViewsHandler();
//        Q_INVOKABLE void updatePropertyPanelModel(dnai::models::Common *model) const;
//		Q_INVOKABLE QModelIndex getIndexMatch(dnai::models::TreeItem * md);
//		Q_INVOKABLE QModelIndex getIndexMatchFromModel(dnai::models::Common *md);
//		Q_INVOKABLE void selectTreeItem(const QModelIndex &index);
//		Q_INVOKABLE void updateNamespace(const QModelIndex &index);
//		Q_INVOKABLE void addContext(int index, int listindex) const;
//		Q_INVOKABLE void addClass(int index, int listindex) const;
//		Q_INVOKABLE void addFunction(int index, int listindex) const;
//		Q_INVOKABLE void addVariable(int index, int listindex) const;
		Q_INVOKABLE void registerTreeView(QQuickItem *tr);
//        Q_INVOKABLE QQuickItem *treeView() const;
//        Q_INVOKABLE void createDeclarationList(const QString& title);
        Q_INVOKABLE void onBuildStart();

	public:
//		models::EntityList *propertyPanelModel() const;
		QVariant namespacebarModel() const { return m_namespacebarmodel; }
		void setNamespacebarModel(const QVariant &ref);
//		void setDeclarationModel(models::DeclarationModel * m);
//		models::DeclarationModel * declarationModel() const { return m_declRef; }
		models::BasicNodeModel *basicNodesModel() const;
//		models::TreeModel *projectModel() const { return m_projectModel; }
//		void setProjectModel(models::TreeModel *model);
//		void setCurrentPath(models::TreeItem *);
//		models::TreeItem *currentPath() const { return m_currentPath; }


    protected:
		std::queue<std::function<void()>> init() override;

	private:
		void initApp();
//		void initDeclarationView();
//		void initPropertyPanel();

	private:
//		controllers::PropertyPanel *m_propertyPanel;
//		models::TreeModel *m_projectModel;
		QVariant m_namespacebarmodel;
//		models::TreeItem *m_currentPath;
		QVariant m_declarationModel;
//		models::DeclarationModel *m_declRef;
        QQuickItem* m_treeView;
		App * m_app;

	private:
//		void createNameSpaceModel(models::TreeItem *item);
//		void setupClassModel(models::Class *cl, int level) const;
//		void setupFunctionModel(models::Function *func) const;
//		void setupContextModel(models::Context *context, int level) const;
//		void setupVariableModel(models::Variable *variable) const;
//		void createDeclarationModel(Project *project) const;
		void clearDeclarationModel() const;
//		void createDeclarationIfMissing(models::Common *c) const;
//		void createDeclarationView() const;
//		void createNameSpaceView() const;
		void createInstructionView() const;

		friend class Manager;
	};
}


#endif
