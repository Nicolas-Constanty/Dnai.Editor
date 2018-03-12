#include <QJsonDocument>
#include <QQmlProperty>

#include "dnai/app.h"
#include "dnai/manager.h"
//#include "dnai/models/treeitem.h"
//#include "dnai/models/namespacebarmodel.h"
//#include "dnai/views/declarationcanvas.h"
#include "dnai/views/declarationview.h"

namespace dnai {
    const QString Manager::project_extension = ".dnaiproject";

    Manager::Manager(QObject *parent): QObject(parent), m_project(nullptr)
	{
		m_viewsHandler = new ViewsHandler();
        m_viewsHandler->load();
	}

    Manager::~Manager()
    {
        delete m_viewsHandler;
        qDebug() << "~" << "Manager";
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

        m_project = new Project(file);
        m_project->save();
    }

	QJsonObject Manager::loadProjectData(const QString &path)
	{
		return Project::loadProjectData(path);
	}


	void Manager::openProject(const QString &path)
    {
        this->openProject(Project::loadProject(path));
    }

    void Manager::openProject(Project *project)
    {
        m_project = project;
//        m_project->declare();
        createTreeModel(m_project);
//        const auto path = static_cast<models::TreeItem*>(m_viewsHandler->projectModel()->index(0,0).internalPointer());
//        m_viewsHandler->setCurrentPath(path);
//        m_viewsHandler->createNameSpaceModel(path);
//		m_viewsHandler->createDeclarationModel(m_project);
//		m_viewsHandler->createDeclarationView();
//		m_viewsHandler->createNameSpaceView();
    }

	//void Manager::createDeclarationView()
	//{
	//	auto layout = App::currentInstance()->appView()->layout();
	//	if (layout->contextView() == nullptr)
 //           layout->setContextView(new views::DeclarationView(layout));
	//}

	//void Manager::createNameSpaceView() const
	//{
	//	const auto layout = App::currentInstance()->appView()->layout();
	//	if (layout->contextView() != nullptr)
	//	{
	//		QMetaObject::invokeMethod(layout, "appendTab", Q_ARG(QVariant, 0), Q_ARG(QVariant, m_currentPath->data(0)));
	//	}
	//}

	//void Manager::createInstructionView()
	//{
	//	auto layout = App::currentInstance()->appView()->layout();
	//	if (layout->contextView() == nullptr)
	//		layout->setContextView(new views::InstructionView(layout));
	//}

	//void Manager::createDeclarationIfMissing(models::Common *c) const
 //   {
 //       if (c->listIndex() + 1 > m_declRef->rowCount())
 //           for (auto i = 0; i < c->listIndex() + 1; i++)
 //           {
 //               if (i + 1 > m_declRef->rowCount())
 //               {
 //                   m_declRef->addDeclaration(new models::Declaration());
 //               }
 //           }
 //   }

 //   void Manager::setupContextModel(models::Context *context, int lvl) const
 //   {
 //       if (!m_declRef || lvl == -1) return;
 //       lvl -= 1;
 //       const auto contexts = context->contexts();
 //       for (auto ctx : contexts)
 //       {
 //           setupContextModel(ctx, lvl);
 //           createDeclarationIfMissing(ctx);
 //           qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(ctx->listIndex(), 0)))->addModel(
	//            ctx);
 //       }

 //       const auto classes = context->classes();
 //       for (auto classe : classes)
 //       {
 //           setupClassModel(classe, lvl);
 //           createDeclarationIfMissing(classe);
 //           qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(classe->listIndex(), 0)))->addModel(
	//            classe);
 //       }

 //       const auto functions = context->functions();
 //       for (auto function : functions)
 //       {
 //           setupFunctionModel(function);
 //       }

 //       const auto variables = context->variables();
 //       for (auto variable : variables)
 //       {
 //           setupVariableModel(variable);
 //       }
 //   }

 //   void Manager::setupClassModel(models::Class *cl, int lvl) const
 //   {
 //       if (!m_declRef || lvl == -1) return;
 //       lvl -= 1;
 //       const auto classes = cl->classes();
 //       for (auto classe : classes)
 //       {
 //           setupClassModel(classe, lvl);
 //           createDeclarationIfMissing(classe);
 //           qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(classe->listIndex(), 0)))->addModel(
	//            classe);
 //       }

 //       const auto functions = cl->functions();
 //       for (auto function : functions)
 //       {
 //           setupFunctionModel(function);
 //       }

 //       const auto variables = cl->attributes();
 //       for (auto variable : variables)
 //       {
 //           setupVariableModel(variable);
 //       }
 //   }

 //   void Manager::setupFunctionModel(models::Function *func) const
 //   {
 //       if (!m_declRef) return;
 //       createDeclarationIfMissing(func);
 //       qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(func->listIndex(), 0)))->addModel(func);
 //   }

 //   void Manager::setupVariableModel(models::Variable *variable) const
 //   {
 //       if (!m_declRef) return;
 //       createDeclarationIfMissing(variable);
 //       qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(variable->listIndex(), 0)))->addModel(variable);
 //   }

 //   void Manager::createDeclarationModel(Project *project) const
 //   {
 //       clearDeclarationModel();
 //       setupContextModel(const_cast<dnai::models::Context *>(project->main()), 0);
 //   }

 //   void Manager::clearDeclarationModel() const
 //   {
 //       m_declRef->clear();
 //   }

 //   void Manager::updateNamespace(const QModelIndex &index)
 //   {
 //       if (!m_declRef || index == QModelIndex()) return;
 //       m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
 //       createNameSpaceModel(m_currentPath);
 //       clearDeclarationModel();
 //       const auto model = m_currentPath->model();
	//	m_declRef->setIsContext(false);
 //       if (model->type() == ModelTypes::Context)
 //       {
	//        const auto ctxView = App::currentInstance()->appView()->layout()->contextView();
	//		if (ctxView && !dynamic_cast<views::DeclarationView*>(ctxView))
	//		{
	//			delete ctxView;
 //               App::currentInstance()->appView()->layout()->setContextView(nullptr);
	//			createDeclarationView();
	//		}
 //           m_declRef->setIsContext(true);
 //           setupContextModel(dynamic_cast<models::Context*>(static_cast<models::Common*>(model)), 0);
 //       }
 //       else if (model->type() == ModelTypes::Class)
 //       {
	//		const auto ctxView = App::currentInstance()->appView()->layout()->contextView();
	//		if (ctxView && !dynamic_cast<views::DeclarationView*>(ctxView))
	//		{
	//			delete ctxView;
 //               App::currentInstance()->appView()->layout()->setContextView(nullptr);
	//			createDeclarationView();
	//		}
 //           setupClassModel(dynamic_cast<models::Class*>(static_cast<models::Common*>(model)), 0);
 //       }
	//	else if (model->type() == ModelTypes::Function)
	//	{
	//		qDebug() << "Hello Function";
	//		const auto ctxView = App::currentInstance()->appView()->layout()->contextView();
	//		if (ctxView && !dynamic_cast<views::InstructionView*>(ctxView))
	//		{
	//			qDebug() << "delete ctx from function";
	//			delete ctxView;
 //               App::currentInstance()->appView()->layout()->setContextView(nullptr);
	//			createInstructionView();
	//		}
	//		setupFunctionModel(dynamic_cast<models::Function*>(static_cast<models::Common*>(model)));
	//	}
 //   }

 //   QModelIndex Manager::getIndexMatch(dnai::models::TreeItem *md)
 //   {
 //       if (!m_declRef || !md)
 //           return QModelIndex();
 //       auto res = m_projectModel->match(m_projectModel->index(0, 0),
 //                                        dnai::models::TreeModel::ItemRole,
 //                                        QVariant::fromValue(md),
 //                                        1, // look *
 //                                        Qt::MatchRecursive | Qt::MatchExactly);

 //       if (res.count())
 //           return res[0];
 //       return QModelIndex();
 //   }

 //   QModelIndex Manager::getIndexMatchFromModel(dnai::models::Common *md)
 //   {
 //       if (!m_declRef || !md)
 //           return QModelIndex();
 //       auto res = m_projectModel->match(m_projectModel->index(0, 0),
 //                                        dnai::models::TreeModel::ItemRole,
 //                                        QVariant::fromValue(md),
 //                                        1, // look *
 //                                        Qt::MatchRecursive | Qt::MatchContains);

 //       if (res.count())
 //           return res[0];
 //       return QModelIndex();
 //   }


 //   void Manager::selectTreeItem(const QModelIndex &index)
 //   {
 //       m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
 //       createNameSpaceModel(m_currentPath);
 //   }

    //void Manager::setProjectModel(models::TreeModel *model)
    //{
    //    if (model == nullptr || m_projectModel == model)
    //        return;
    //    m_projectModel = model;
    //    emit projectModelChanged(model);
    //}

 /*   void Manager::setNamespacebarModel(const QVariant &ref)
    {
        m_namespacebarmodel = ref;
        emit namespacebarModelChanged(ref);
    }*/

    //void Manager::setDeclarationModel(models::DeclarationModel *m)
    //{
    //    m_declRef = m;
    //    emit declarationModelChanged(m);
    //}

    void Manager::createTreeModel(Project *project)
    {
//        m_viewsHandler->setProjectModel(new models::TreeModel(project));
    }

    //void Manager::createNameSpaceModel(models::TreeItem *item)
    //{
    //    QList<QObject *> temp;

    //    auto ns = new models::NameSpaceBarItem();
    //    ns->setPath(item->data(0).toString());
    //    ns->setAsChild(item->childCount());
    //    ns->setIdx(item->idxmodel());
    //    ns->setModel(item);
    //    temp.append(ns);
    //    while (item->parentItem()->parentItem())
    //    {
    //        item = item->parentItem();
    //        ns = new models::NameSpaceBarItem();
    //        ns->setPath(item->data(0).toString());
    //        ns->setAsChild(item->childCount());
    //        ns->setIdx(item->idxmodel());
    //        ns->setModel(item);
    //        temp.append(ns);
    //    }
    //    std::reverse(temp.begin(), temp.end());
    //    setNamespacebarModel(QVariant::fromValue(temp));
    //}

    //void Manager::addContext(const int index, const int listindex) const
    //{
    //    qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex , 0)))->addModel(new models::Context(-1, "Context", "", QVector2D(), index, listindex));
    //}

    //void Manager::addClass(const int index, const int listindex) const
    //{
    //    qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex , 0)))->addModel(new models::Class(-1, "Class", "", QVector2D(), index, listindex));
    //}

    //void Manager::addFunction(const int index, const int listindex) const
    //{
    //    qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex , 0)))->addModel(new models::Function(-1, "Function", "", QVector2D(), index, listindex));
    //}

    //void Manager::addVariable(const int index, const int listindex) const
    //{
    //    qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex , 0)))->addModel(new models::Variable(-1, "Variable", "", QVector2D(), "generic", false, index, listindex));
    //}

    void Manager::setAppViewLayout(dnai::views::Layout *l) const
    {
		App::currentInstance()->appView()->setLayout(l);
    }

	//void Manager::registerTreeView(QQuickItem *tr)
	//{
	//	m_treeView = tr;
	//}

	//QQuickItem* Manager::treeView() const
	//{
	//	return m_treeView;
	//}

	//models::BasicNodeModel* Manager::basicNodesModel() const
	//{
	//	return App::currentInstance()->basicNodesModel();
	//}

    Session * Manager::session() const
    {
        return const_cast<Session *>(App::currentInstance()->session());
    }

    ViewsHandler *Manager::views() const
    {
        return m_viewsHandler;
    }

	void Manager::createNode(QObject *nodeModel)
	{
        QString path = "qrc:/resources/Components/Node.qml";
        QQmlComponent component(App::getEngineInstance(), path);
        QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(App::getEngineInstance()->rootContext()));
        QQmlProperty model(obj, "model", App::getEngineInstance());
        model.write(QVariant::fromValue(m_viewsHandler->basicNodesModel()->createNode(static_cast<enums::QInstructionID::Instruction_ID>(nodeModel->property("instruction_id").toInt()))));
        obj->setParentItem(App::instructionView()->canvas()->content());
        component.completeCreate();
    }
    bool Manager::isMac()
    {
#ifdef Q_OS_MAC
        return true;
#else
        return false;
#endif
    }
}
