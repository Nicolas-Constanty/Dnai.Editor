#include <QDateTime>
#include "dnai/app.h"
#include "dnai/viewshandler.h"
#include "dnai/models/namespacebaritem.h"
#include "dnai/views/declarationview.h"

#ifdef _WIN32
#include "../../lib/WinToast/wintoastlib.h"
using namespace WinToastLib;
#endif

namespace dnai
{
    ViewsHandler::ViewsHandler() : QObject(nullptr), /*m_propertyPanel(nullptr),*/ /*m_projectModel(nullptr),*/
                                   /*m_currentPath(nullptr),*/
        /*m_treeView(nullptr),*/ m_app(nullptr)
	{
	}

//    void ViewsHandler::updatePropertyPanelModel(dnai::models::Common* model) const
//	{
//        const auto prop = new models::EntityList(static_cast<models::IModel*>(model));
//		if (m_propertyPanel->model() == nullptr)
//			m_propertyPanel->asyncCreate(prop);
//		else
//			m_propertyPanel->setModel(prop);
//		emit propertyPanelModelChanged(prop);
//	}

//	models::EntityList* ViewsHandler::propertyPanelModel() const
//	{
////		return m_propertyPanel->model();
//	}

	void ViewsHandler::setNamespacebarModel(const QVariant& ref)
	{
		m_namespacebarmodel = ref;
		emit namespacebarModelChanged(ref);
	}

//	void ViewsHandler::setDeclarationModel(models::DeclarationModel* m)
//	{
//		m_declRef = m;
//		emit declarationModelChanged(m);
//	}

//	models::BasicNodeModel* ViewsHandler::basicNodesModel() const
//	{
//		return m_app->basicNodesModel();
//	}

//	void ViewsHandler::setProjectModel(models::TreeModel* model)
//	{
//		if (model == nullptr || m_projectModel == model)
//			return;
//		m_projectModel = model;
//		emit projectModelChanged(model);
//	}

//	void ViewsHandler::setCurrentPath(models::TreeItem *path)
//	{
//		m_currentPath = path;
//	}

	std::queue<std::function<void()>> ViewsHandler::init()
	{
		std::queue<std::function<void()>> funcs;
        funcs.push(std::bind(&ViewsHandler::initApp, this));
        funcs.push(std::bind(&ViewsHandler::initDeclarationView, this));
        funcs.push(std::bind(&ViewsHandler::initPropertyPanel, this));
		return funcs;
	}

	void ViewsHandler::initApp()
	{
		m_app = App::currentInstance();
	}

//	void ViewsHandler::initDeclarationView()
//	{
//		m_declRef = new models::DeclarationModel();
//	}

//	void ViewsHandler::initPropertyPanel()
//	{
//		m_propertyPanel = new controllers::PropertyPanel();
//	}

//	void ViewsHandler::addContext(const int index, const int listindex) const
//	{
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex, 0)))->addModel(new models::Context(-1, "Context", "", QVector2D(), index, listindex));
//	}

//	void ViewsHandler::addClass(const int index, const int listindex) const
//	{
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex, 0)))->addModel(new models::Class(-1, "Class", "", QVector2D(), index, listindex));
//	}

//	void ViewsHandler::addFunction(const int index, const int listindex) const
//	{
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex, 0)))->addModel(new models::Function(-1, "Function", "", QVector2D(), index, listindex));
//	}

//	void ViewsHandler::addVariable(const int index, const int listindex) const
//	{
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(listindex, 0)))->addModel(new models::Variable(-1, "Variable", "", QVector2D(), "generic", false, index, listindex));
//	}

//	void ViewsHandler::registerTreeView(QQuickItem *tr)
//	{
//		m_treeView = tr;
//	}

//	QQuickItem* ViewsHandler::treeView() const
//	{
//        return m_treeView;
//    }

//     void ViewsHandler::createDeclarationList(const QString &title)
//    {
//        m_declRef->addDeclaration(new models::Declaration(title));
//    }

//	void ViewsHandler::createNameSpaceModel(models::TreeItem *item)
//	{
//		QList<QObject *> temp;

//        if (!item || !item->row()) return;
//		auto ns = new models::NameSpaceBarItem();
//		ns->setPath(item->data(0).toString());
//		ns->setAsChild(item->childCount());
//		ns->setIdx(item->idxmodel());
//		ns->setModel(item);
//		temp.append(ns);
//		while (item->parentItem()->parentItem())
//		{
//			item = item->parentItem();
//			ns = new models::NameSpaceBarItem();
//			ns->setPath(item->data(0).toString());
//			ns->setAsChild(item->childCount());
//			ns->setIdx(item->idxmodel());
//			ns->setModel(item);
//			temp.append(ns);
//		}
//		std::reverse(temp.begin(), temp.end());
//		setNamespacebarModel(QVariant::fromValue(temp));
//	}

//	void ViewsHandler::createDeclarationView() const
//	{
//		auto layout = m_app->appView()->layout();
//		if (layout->contextView() == nullptr)
//			layout->setContextView(new views::DeclarationView(layout));
//	}

//	void ViewsHandler::createNameSpaceView() const
//	{
//		const auto layout = m_app->appView()->layout();
//		if (layout->contextView() != nullptr)
//		{
//			QMetaObject::invokeMethod(layout, "appendTab", Q_ARG(QVariant, 0), Q_ARG(QVariant, m_currentPath->data(0)));
//		}
//	}

//	void ViewsHandler::createInstructionView() const
//	{
//		auto layout = m_app->appView()->layout();
//		if (layout->contextView() == nullptr)
//			layout->setContextView(new views::InstructionView(layout));
//	}

//	void ViewsHandler::createDeclarationIfMissing(models::Common *c) const
//	{
//		if (c->listIndex() + 1 > m_declRef->rowCount())
//			for (auto i = 0; i < c->listIndex() + 1; i++)
//			{
//				if (i + 1 > m_declRef->rowCount())
//				{
//					m_declRef->addDeclaration(new models::Declaration());
//				}
//			}
//	}

//	void ViewsHandler::setupContextModel(models::Context *context, int lvl) const
//	{
//		if (!m_declRef || lvl == -1) return;
//		lvl -= 1;
//		const auto contexts = context->contexts();
//		for (auto ctx : contexts)
//		{
//			setupContextModel(ctx, lvl);
//			createDeclarationIfMissing(ctx);
//			qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(ctx->listIndex(), 0)))->addModel(
//				ctx);
//		}

//		const auto classes = context->classes();
//		for (auto classe : classes)
//		{
//			setupClassModel(classe, lvl);
//			createDeclarationIfMissing(classe);
//			qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(classe->listIndex(), 0)))->addModel(
//				classe);
//		}

//		const auto functions = context->functions();
//		for (auto function : functions)
//		{
//			setupFunctionModel(function);
//		}

//		const auto variables = context->variables();
//		for (auto variable : variables)
//		{
//			setupVariableModel(variable);
//		}
//	}

//	void ViewsHandler::setupClassModel(models::Class *cl, int lvl) const
//	{
//		if (!m_declRef || lvl == -1) return;
//		lvl -= 1;
//		const auto classes = cl->classes();
//		for (auto classe : classes)
//		{
//			setupClassModel(classe, lvl);
//			createDeclarationIfMissing(classe);
//			qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(classe->listIndex(), 0)))->addModel(
//				classe);
//		}

//		const auto functions = cl->functions();
//		for (auto function : functions)
//		{
//			setupFunctionModel(function);
//		}

//		const auto variables = cl->attributes();
//		for (auto variable : variables)
//		{
//			setupVariableModel(variable);
//		}
//	}

//	void ViewsHandler::setupFunctionModel(models::Function *func) const
//	{
//		if (!m_declRef) return;
//		createDeclarationIfMissing(func);
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(func->listIndex(), 0)))->addModel(func);
//	}

//	void ViewsHandler::setupVariableModel(models::Variable *variable) const
//	{
//		if (!m_declRef) return;
//		createDeclarationIfMissing(variable);
//		qvariant_cast<models::Declaration *>(m_declRef->data(m_declRef->index(variable->listIndex(), 0)))->addModel(variable);
//	}

//	void ViewsHandler::createDeclarationModel(Project *project) const
//	{
//		clearDeclarationModel();
//		setupContextModel(const_cast<dnai::models::Context *>(project->main()), 0);
//	}

//	void ViewsHandler::clearDeclarationModel() const
//	{
//		m_declRef->clear();
//	}

//	void ViewsHandler::updateNamespace(const QModelIndex &index)
//	{
//		if (!m_declRef || index == QModelIndex()) return;
//		m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
//		createNameSpaceModel(m_currentPath);
//		clearDeclarationModel();
//		const auto model = m_currentPath->model();
//		m_declRef->setIsContext(false);
//		if (model->type() == ModelTypes::Context)
//		{
//			const auto ctxView = m_app->appView()->layout()->contextView();
//			if (ctxView && !dynamic_cast<views::DeclarationView*>(ctxView))
//			{
//				delete ctxView;
//				m_app->appView()->layout()->setContextView(nullptr);
//				createDeclarationView();
//			}
//			m_declRef->setIsContext(true);
//			setupContextModel(dynamic_cast<models::Context*>(static_cast<models::Common*>(model)), 0);
//		}
//		else if (model->type() == ModelTypes::Class)
//		{
//			const auto ctxView = m_app->appView()->layout()->contextView();
//			if (ctxView && !dynamic_cast<views::DeclarationView*>(ctxView))
//			{
//				delete ctxView;
//				m_app->appView()->layout()->setContextView(nullptr);
//				createDeclarationView();
//			}
//			setupClassModel(dynamic_cast<models::Class*>(static_cast<models::Common*>(model)), 0);
//		}
//		else if (model->type() == ModelTypes::Function)
//		{
//			qDebug() << "Hello Function";
//			const auto ctxView = m_app->appView()->layout()->contextView();
//			if (ctxView && !dynamic_cast<views::InstructionView*>(ctxView))
//			{
//				qDebug() << "delete ctx from function";
//				delete ctxView;
//				m_app->appView()->layout()->setContextView(nullptr);
//				createInstructionView();
//			}
//			setupFunctionModel(dynamic_cast<models::Function*>(static_cast<models::Common*>(model)));
//		}
//	}

//	QModelIndex ViewsHandler::getIndexMatch(dnai::models::TreeItem *md)
//	{
//		if (!m_declRef || !md)
//			return QModelIndex();
//		auto res = m_projectModel->match(m_projectModel->index(0, 0),
//			dnai::models::TreeModel::ItemRole,
//			QVariant::fromValue(md),
//			1, // look *
//			Qt::MatchRecursive | Qt::MatchExactly);

//		if (res.count())
//			return res[0];
//		return QModelIndex();
//	}

//	QModelIndex ViewsHandler::getIndexMatchFromModel(dnai::models::Common *md)
//	{
//		if (!m_declRef || !md)
//			return QModelIndex();
//		auto res = m_projectModel->match(m_projectModel->index(0, 0),
//			dnai::models::TreeModel::ItemRole,
//			QVariant::fromValue(md),
//			1, // look *
//			Qt::MatchRecursive | Qt::MatchContains);

//		if (res.count())
//			return res[0];
//		return QModelIndex();
//	}


//	void ViewsHandler::selectTreeItem(const QModelIndex &index)
//	{
//		m_currentPath = static_cast<models::TreeItem*>(index.internalPointer());
//		createNameSpaceModel(m_currentPath);
//	}

#ifdef _WIN32
    class CustomHandler : public IWinToastHandler {
    public:
        void toastActivated() const {
            std::wcout << L"The user clicked in this toast" << std::endl;
        }

        void toastActivated(int actionIndex) const {
            std::wcout << L"The user clicked on button #" << actionIndex << L" in this toast" << std::endl;
        }

        void toastFailed() const {
            std::wcout << L"Error showing current toast" << std::endl;
        }
        void toastDismissed(WinToastDismissalReason state) const {
            switch (state) {
            case UserCanceled:
                std::wcout << L"The user dismissed this toast" << std::endl;
                break;
            case ApplicationHidden:
                std::wcout <<  L"The application hid the toast using ToastNotifier.hide()" << std::endl;
                break;
            case TimedOut:
                std::wcout << L"The toast has timed out" << std::endl;
                break;
            default:
                std::wcout << L"Toast not activated" << std::endl;
                break;
            }
        }
    };
#endif
    void ViewsHandler::onBuildStart()
    {
#ifdef _WIN32
       WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText04);
//       templ.setImagePath(ui->imagePath->text().toStdWString());
       templ.setTextField(QString("Build Start at :").toStdWString(), WinToastTemplate::FirstLine);
       QDateTime dateTime = dateTime.currentDateTime();
       QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
       templ.setTextField(dateTimeString.toStdWString(), WinToastTemplate::SecondLine);
       templ.setTextField(QString("by Nicolas C").toStdWString(), WinToastTemplate::ThirdLine);
       templ.setExpiration(10000);

       if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
           qDebug() << "Error", "Could not launch your toast notification!";
//           QMessageBox::warning(this, "Error", "Could not launch your toast notification!");
       }
#endif
    }

}
