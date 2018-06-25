#include <tuple>

#include <QObject>
#include <QQmlProperty>
#include <QQuickView>
#include <QJsonDocument>


#include "dnai/editor.h"
#include "dnai/solution.h"
#include "dnai/project.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"
#include "dnai/interfaces/iviewzone.h"
#include "dnai/app.h"
#include "dnai/views/canvasnode.h"
#include "dnai/models/gui/declarable/function.h"
#include "dnai/core/handlermanager.h"
#include "dnai/exceptions/guiexception.h"
#include "dnai/views/genericnode.h"

namespace dnai
{
	Editor &Editor::m_instance = *(new Editor());

	Editor::Editor() : m_solution(nullptr)
		, m_selection(nullptr)
		, m_editorView(nullptr)
		, m_propertyView(nullptr)
        , m_propertyPanelProperties(nullptr)
	    , m_contextMenuModel(nullptr)
        , m_settings(nullptr)
	{
	}

	Editor::~Editor()
	{
		delete m_propertyPanelProperties;
	}

	const QString& Editor::version() const
	{
		return m_version;
	}

	void Editor::setVersion(const QString& version)
	{
		if (version == m_version)
			return;
		m_version = version;
	}

	void Editor::save()
	{
		m_solution->save();
	}

	void Editor::restoreViewState(const QJsonObject& obj)
	{
        Q_UNUSED(obj)
        exceptions::ExceptionManager::throwException(exceptions::NotImplemented());
	}

	void Editor::saveViewState()
	{
		QJsonObject obj;
		QJsonArray arr;
		for (const auto view : m_viewZones)
		{
			if (const auto v = dynamic_cast<interfaces::IViewZone *>(view))
			{
				QJsonObject var;
				v->serialize(var);
				arr.append(var);
			}
		}
		obj["views"] = arr;
	}

	void Editor::openSolution()
	{
        for (auto proj : m_solution->projects())
            if (const auto p = dynamic_cast<Project*>(proj))
                gcore::HandlerManager::Instance().Project().create(p, false);
	}

	void Editor::loadSolution(const QString& filename)
    {
        setLoaded(true);
		m_solution = new Solution();
		if (!filename.isEmpty())
            m_solution->load(filename);

        m_solutionName = filename;
    }

    void Editor::newEditor(const QString &solutionToLoad)
    {
        QProcess newEdit;

        newEdit.setProgram(m_appname);
        newEdit.setArguments({ solutionToLoad });
        newEdit.startDetached();
        newEdit.waitForStarted();
        return;
    }

    void Editor::startApp()
    {
       App::currentInstance()->load();

       QObject::connect(&dnai::gcore::HandlerManager::Instance().Function(), SIGNAL(instructionAdded(models::Entity*,models::gui::Instruction*)),
                        this, SLOT(onInstructionAdded(models::Entity*,models::gui::Instruction*)));
       QObject::connect(&dnai::gcore::HandlerManager::Instance().Function(), SIGNAL(addInstructionError(quint32,quint32,QList<quint32>,QString)),
                        this, SLOT(onAddInstructionError(quint32,quint32,QList<quint32>,QString)));

       QObject::connect(dnai::gcore::HandlerManager::Instance().Function().instruction(), SIGNAL(dataLinked(dnai::models::Entity *, dnai::models::gui::Instruction *, QString, dnai::models::gui::Instruction *, QString)),
                        this, SLOT(onInstructionDataLinked(dnai::models::Entity *, dnai::models::gui::Instruction *, QString, dnai::models::gui::Instruction *, QString)));

       QObject::connect(dnai::gcore::HandlerManager::Instance().Function().instruction(), SIGNAL(executionLinked(dnai::models::Entity*,dnai::models::gui::Instruction*,quint32,dnai::models::gui::Instruction*)),
                        this, SLOT(onExecutionLinked(dnai::models::Entity*,dnai::models::gui::Instruction*,quint32,dnai::models::gui::Instruction*)));

       QObject::connect(&dnai::gcore::HandlerManager::Instance().Function(), SIGNAL(entryPointSet(dnai::models::Entity*, dnai::models::gui::Instruction*)),
                        this, SLOT(onEntryPointSet(dnai::models::Entity *, dnai::models::gui::Instruction *)));


       QObject::connect(dnai::gcore::HandlerManager::Instance().Function().instruction(), SIGNAL(executionUnlinked(dnai::models::Entity*,dnai::models::gui::Instruction*,quint32)),
                        this, SLOT(onExecutionUnlinked(dnai::models::Entity*,dnai::models::gui::Instruction*,quint32)));

       QObject::connect(dnai::gcore::HandlerManager::Instance().Function().instruction(), SIGNAL(dataUnlinked(dnai::models::Entity*, dnai::models::gui::Instruction*, QString)),
                        this, SLOT(onDataUnlinked(dnai::models::Entity*,dnai::models::gui::Instruction*,QString)));

       contextMenuModel()->setup();
    }

	void Editor::closeSolution()
	{
        setLoaded(false);
		m_solution->close();
	}

    void Editor::notifyInformation(QString const &text, std::function<void ()> func) {
        m_toasterManagerService.notifyInformation(text, func);
    }

    void Editor::notifySuccess(QString const &text, std::function<void ()> func) {
        m_toasterManagerService.notifySuccess(text, func);
    }

    void Editor::notifyError(QString const &text, std::function<void ()> func) {
        m_toasterManagerService.notifyError(text, func);
    }

    void Editor::notifyWarning(QString const &text, std::function<void ()> func) {
        m_toasterManagerService.notifyWarning(text, func);
    }

    void Editor::buildSolution() {
        QString path = m_solution->fileName();
        gcore::HandlerManager::Instance().Global().save(QUrl(path.replace(".dnaisolution", ".dnai")).toLocalFile());
    }

	const QList<interfaces::ICommand*>& Editor::actions() const
	{
		return m_actions;
	}

	const QObject& Editor::selection() const
	{
		return *m_selection;
	}

	const QList<QObject*>& Editor::selections() const
	{
		return m_selections;
	}

	const QList<QQuickItem *>& Editor::views() const
	{
		return m_viewZones;
	}

    bool Editor::loaded() const {
        return (m_loaded);
    }

    void Editor::setLoaded(bool newLoaded) {
        this->m_loaded = newLoaded;
        emit loadedChanged(this->m_loaded);
    }

	QQuickItem *Editor::selectedView() const
	{
		return m_seletedItem;
	}

    bool Editor::isSolutionLoad() const {
        return (m_solution != nullptr);
    }

	void Editor::selectView(QQuickItem* i)
	{
		m_seletedItem = i;
		if (!m_viewZones.contains(m_seletedItem))
			addView(i);
	}

	void Editor::selectProject(Project* proj)
	{
		m_solution->selectProject(proj);
	}

	Editor& Editor::instance()
	{
        return m_instance;
    }

    void Editor::setSolution(dnai::Solution* sol)
	{
		if (m_solution == sol)
			return;
		m_solution = sol;
        emit solutionChanged(sol);
    }

	PropertyPanelProperties * Editor::propertyPanelProperties()
	{
		if (!m_propertyPanelProperties)
			m_propertyPanelProperties = new PropertyPanelProperties();
		return m_propertyPanelProperties;
	}

	interfaces::ISolution *Editor::solution() const
    {
        return m_solution;
    }

    Solution *Editor::getSolution() const
    {
        return dynamic_cast<Solution*>(solution());
    }

	void Editor::addView(QQuickItem* vz)
	{
		if (vz == nullptr || m_viewZones.contains(vz))
            return;
		m_viewZones.append(vz);
	}

	views::EditorView *Editor::mainView() const
	{
		return m_editorView;
	}

    const QString &Editor::solutionName() const
    {
        return m_solutionName;
    }

	dnai::models::ContextMenuModel* Editor::contextMenuModel()
	{
		if (m_contextMenuModel == nullptr)
		{
			QFile file(":resources/Nodes/Operators.json");

			if (!file.open(QIODevice::ReadOnly)) {
				qWarning() << "Couldn't open file: " << file.errorString();
                return nullptr;
			}

			const QByteArray data = file.readAll();

			try {
				const QJsonObject obj(QJsonDocument::fromJson(data).object());
				m_contextMenuModel = new dnai::models::ContextMenuModel(obj);
			}
			catch (std::exception &e) {
				Q_UNUSED(e)
					exceptions::ExceptionManager::throwException(exceptions::GuiExeption("Error : Corrupted Solution file"));
				qWarning("Couldn't parse file.");
			}
			file.close();
		}
		return m_contextMenuModel;
	}

	void Editor::setContextMenuModel(dnai::models::ContextMenuModel* ctx)
	{
		if (ctx == m_contextMenuModel)
			return;
		m_contextMenuModel = ctx;
		emit contextMenuModelChanged(ctx);
	}

	void Editor::updateContextMenuModel(dnai::models::Entity* entity) const
	{
		const auto function = dynamic_cast<models::gui::declarable::Function *>(entity->guiModel());
		if (function == nullptr) return;
		m_contextMenuModel->clearParameters();
		m_contextMenuModel->clearReturns();
		for (auto param : function->inputs())
		{
			m_contextMenuModel->appendParameter(param);
		}
		for (auto ret : function->outputs())
		{
			m_contextMenuModel->appendReturn(ret);
		}
		emit contextMenuModelChanged(m_contextMenuModel);
	}

	void Editor::registerEditorView(views::EditorView* view)
	{
		m_editorView = view;
    }

    Session *Editor::session() const
    {
        return &App::currentInstance()->session();
    }

    void Editor::setAppName(const QString &name)
    {
        m_appname = name;
    }

    void Editor::setSolutionName(const QString &name)
    {
        m_solutionName = name;
    }

	QQuickItem * Editor::createNodeQMLComponent(models::ContextMenuItem *node, models::Entity *func, models::gui::Instruction *instruction, QQuickItem *parent) const
    {
        /*
         * Node Components
         */
        QQmlComponent nodeComponent(App::getEngineInstance(), "qrc:/resources/Components/Node.qml");

        /*
         * Create the Node
         */
        QQuickItem *nodeObj = qobject_cast<QQuickItem*>(nodeComponent.beginCreate(App::getEngineInstance()->rootContext()));
        QQmlProperty model(nodeObj, "model", App::getEngineInstance());
        QQmlProperty instruction_model(nodeObj, "instruction_model", App::getEngineInstance());
        QQmlProperty function_entity(nodeObj, "function_entity", App::getEngineInstance());

        /*
         * Write properties
         */
        model.write(QVariant::fromValue(node));
        instruction_model.write(QVariant::fromValue(instruction));
        function_entity.write(QVariant::fromValue(func));

        /*
         * Set parent and position
         */
        nodeObj->setParentItem(parent);
        nodeObj->setX(instruction->x());
        nodeObj->setY(instruction->y());

        nodeComponent.completeCreate();

		return nodeObj;
    }

    void Editor::onInstructionAdded(models::Entity *func, models::gui::Instruction *instruction)
    {
        if (m_pendingInstruction.empty())
            return;

        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);

        quint32 x, y;
        models::ContextMenuItem *node;

        std::tie(node, x, y) = m_pendingInstruction.front();

        instruction->setX(x - canvas->content()->x());
        instruction->setY(y - canvas->content()->y());

        if (createNodeQMLComponent(node, func, instruction, canvas->content()) == nullptr)
        {
			notifyWarning("Cannot create qml node");
        }

        instruction->setNodeMenuPath(node->fullPath());

        /*
         * Building inputs
         */
        if (instruction->inputs().empty())
        {
            QList<models::gui::Input *> inputs;

            for (QString const &curr : node->inputNames())
            {
                models::gui::Input *toadd = new models::gui::Input();

                toadd->setName(curr);
                inputs.append(toadd);
            }

            instruction->setInputs(inputs);
        }

        /*
         * Building outputs
         */
        if (instruction->outputs().empty())
        {
            QList<models::gui::Output *> outputs;

            for (QString const &curr : node->outputNames())
            {
                models::gui::Output *toadd = new models::gui::Output();

                toadd->setName(curr);
                outputs.append(toadd);
            }

            instruction->setOutputs(outputs);
        }

        m_pendingInstruction.pop();
    }

    void Editor::onAddInstructionError(quint32 func, quint32 type, const QList<quint32> &args, const QString &msg)
    {
        Q_UNUSED(func)
        Q_UNUSED(type)
        Q_UNUSED(args)
        Q_UNUSED(msg)

        if (!m_pendingInstruction.empty())
            m_pendingInstruction.pop();
    }

    void Editor::onInstructionDataLinked(models::Entity *func, models::gui::Instruction *from, QString output, models::gui::Instruction *to, QString input)
    {
        Q_UNUSED(output);
        Q_UNUSED(input);
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        views::GenericNode *n1 = nullptr;
        views::GenericNode *n2 = nullptr;
        const auto content =  canvas->content();
        for (auto i = 0; i< content->childItems().size(); i++)
        {
            auto node = dynamic_cast<dnai::views::GenericNode*>(content->childItems().at(i));
            if (node)
            {
                if (n1 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == to)
                {
                    n1 = node;
                }
                else if (n2 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == from)
                {
                    n2 = node;
                }
                if (n1 && n2)
                    break;
            }
        }
        if (n1 && n2)
        {
            const auto function = dynamic_cast<models::gui::declarable::Function *>(func->guiModel());
            if (function)
            {
                n1->createLink(function->iolinks().last(), n2);
            }
        }
    }

    void Editor::onExecutionLinked(models::Entity *func, models::gui::Instruction *from, quint32 outPin, models::gui::Instruction *to)
    {
        Q_UNUSED(outPin);
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        views::GenericNode *n1 = nullptr;
        views::GenericNode *n2 = nullptr;
        const auto content =  canvas->content();
        for (auto i = 0; i< content->childItems().size(); i++)
        {
            auto node = dynamic_cast<dnai::views::GenericNode*>(content->childItems().at(i));
            if (node)
            {
                if (n1 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == from)
                {
                    n1 = node;
                }
                else if (n2 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == to)
                {
                    n2 = node;
                }
                if (n1 && n2)
                    break;
            }
        }
        if (n1 && n2)
        {
            const auto function = dynamic_cast<models::gui::declarable::Function *>(func->guiModel());
            if (function)
            {
                n1->createFlowLink(function->flowlinks().last(), n2);
            }
        }
    }

    void Editor::onEntryPointSet(models::Entity *func, models::gui::Instruction *entry)
    {
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        const auto content =  canvas->content();
        for (auto i = 0; i< content->childItems().size(); i++)
        {
            auto node = dynamic_cast<dnai::views::GenericNode*>(content->childItems().at(i));
            if (node && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == entry)
            {
                const auto entry = dynamic_cast<dnai::views::GenericNode*>(canvas->entry());
                entry->createFlowLink(new models::gui::FlowLink(), node);
                break;
            }
        }
    }

    void Editor::onExecutionUnlinked(models::Entity *func, models::gui::Instruction *from, quint32 outPin)
    {
        Q_UNUSED(func)
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        const auto content =  canvas->content();
        for (auto i = 0; i< content->childItems().size(); i++)
        {
            auto node = dynamic_cast<dnai::views::GenericNode*>(content->childItems().at(i));
            if (node && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == from)
            {
                node->unlinkFlow(outPin);
                break;
            }
        }
    }

    void Editor::onDataUnlinked(models::Entity *func, models::gui::Instruction *instruction, QString input)
    {
        Q_UNUSED(func)
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        const auto content =  canvas->content();
        for (auto i = 0; i< content->childItems().size(); i++)
        {
            auto node = dynamic_cast<dnai::views::GenericNode*>(content->childItems().at(i));
            if (node && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == instruction)
            {
                const auto ilist = instruction->inputs();
                auto index = 0;
                for(models::gui::Input* in : ilist)
                {
                    if (in->data().name == input)
                    {
                        node->unlinkIo(index);
                        break;
                    }
                    ++index;
                }
                break;
            }
        }
    }

    void Editor::createNode(models::Entity *entity, models::ContextMenuItem *node, qint32 x, qint32 y)
    {
	    const auto function = dynamic_cast<models::gui::declarable::Function *>(entity->guiModel());
        if (function == nullptr) return;

        QList<quint32> topass;

        for (qint32 curr : node->construction()) {
            topass.append(static_cast<quint32>(curr));
        }

        //call the core function to add instruction
        dnai::gcore::HandlerManager::Instance().Function().addInstruction(entity->id(), node->instructionId(), topass);

        //save the positions when the instruction will be added
        m_pendingInstruction.emplace(node, x, y);
    }

    void Editor::checkVersion()
    {
        auto app = App::currentInstance();
        app->versionsUpdater();
      //  app->onNotifyVersionChanged();
    }

    //models::EntityList *Editor::entities()
    //{
    //	return models::Entity::m_entities;
    //}

    void Editor::registerMainView(QObject *mainView) {
        m_mainView = static_cast<QQuickWindow*>(mainView);
    }


    void Editor::addProject(QString const &proj_name, QString const &proj_desc) {
        QString glpath = "file:///" + m_solution->path() + "/" + proj_name + ".dnaiproject";

        for (const interfaces::IProject *currProj : m_solution->projects()) {
            if (currProj->fileName() == glpath)
            {
                notifyError("Project " + proj_name + " already exist");
                return;
            }
        }

        auto p = new Project(glpath);

        p->setName(proj_name);
        p->setDescription(proj_desc);
        m_solution->addProject(p);
        p->setSaved(false);

        gcore::HandlerManager::Instance().Project().create(p);

        m_solution->save();

        emit solutionChanged(dynamic_cast<dnai::Solution *>(m_solution));
    }

    bool Editor::createSolution(const QString &name,
                                const QString &description,
                                const QString &path,
                                const QString &proj_name,
                                const QString &proj_desc)
    {
        const auto sol_path = path + "/" + name + ".dnaisolution";
        const auto proj_path = path + "/" + proj_name + ".dnaiproject";

        if (QFileInfo::exists(QUrl(sol_path).toLocalFile()))
        {
            notifyError("Unable to create solution at " + sol_path + " (file exist)");
            return false;
        }

        if (QFileInfo::exists(QUrl(proj_path).toLocalFile()))
        {
            notifyError("Cannot create project at " + proj_path + " (file exist)");
            return false;
        }

        auto solution = new Solution(sol_path);
        solution->setName(name);
        solution->setDescription(description);
        auto p = new Project(proj_path);
        p->setName(proj_name);
        p->setDescription(proj_desc);
        solution->addProject(p);
        solution->save();
        return true;
    }

    QQuickWindow *Editor::mainView()  {
        return m_mainView;
    }

    QQuickItem *Editor::qmlMainView() {
        return m_mainView->contentItem();
    }

    void Editor::registerPropertyView(QQuickItem *view)
    {
		m_propertyView = view;
    }

	QQuickItem *Editor::propertyView() const
	{
        return m_propertyView;
    }

	void Editor::loadFunction(dnai::models::Entity* entity) const
	{
		const auto function = dynamic_cast<models::gui::declarable::Function *>(entity->guiModel());
		if (function == nullptr) return;
		const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
		if (!view)
		{
			throw std::runtime_error("No canvas view found!");
        }
        const auto canvas = dynamic_cast<views::CanvasNode *>(view);

        updateContextMenuModel(entity);

        QList<views::GenericNode *> nodes;

        /*
         * Create entry point node
         */
        QQmlComponent nodeEntryPoint(App::getEngineInstance(), "qrc:/resources/Components/NodeEntryPoint.qml");
        views::GenericNode *entryPointObj = dynamic_cast<views::GenericNode *>(qobject_cast<QQuickItem*>(nodeEntryPoint.beginCreate(App::getEngineInstance()->rootContext())));
        QQmlProperty function_entity(entryPointObj, "function_entity", App::getEngineInstance());
        models::gui::Instruction *entryInstr = function->entryPoint();

        function_entity.write(QVariant::fromValue(entity));
        entryPointObj->setParentItem(canvas->content());
        entryPointObj->setX(function->entryPointX());
        entryPointObj->setY(function->entryPointY());
        nodeEntryPoint.completeCreate();

        nodes.append(entryPointObj);

        canvas->registerEntry(entryPointObj);

        /*
         * Create all nodes
         */
        const auto instructionsMap = m_contextMenuModel->instructions();

        for (models::gui::Instruction *instruction : function->instructions())
		{
            QString nodePath = instruction->nodeMenuPath();

            if (instructionsMap.contains(nodePath))
            {
                nodes.append(dynamic_cast<views::GenericNode *>(createNodeQMLComponent(instructionsMap[nodePath], entity, instruction, canvas->content())));
            }
            else
            {
                throw std::runtime_error("No such node \"" + nodePath.toStdString() + "\" in context menu");
            }
		}

        /*
         * Create io links
         */
        for (models::gui::IoLink *iolink : function->iolinks())
        {
			const auto inputInstruction = function->getInstruction(iolink->data().inputUuid);
			const auto outputInstruction = function->getInstruction(iolink->data().outputUuid);
			views::GenericNode *n1 = nullptr;
			views::GenericNode *n2 = nullptr;
			for (auto node : nodes)
			{
				if (n1 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == inputInstruction)
				{
					n1 = node;
				}
				else if (n2 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == outputInstruction)
				{
					n2 = node;
				}
				if (n1 && n2)
					break;
			}
			if (!n1 || !n2) return;
			n1->createLink(iolink, n2);
        }

        /*
         * Create flow links
         */
        for (auto flowlink : function->flowlinks())
		{
			const auto inputInstruction = function->getInstruction(flowlink->data().from);
			const auto outputInstruction = function->getInstruction(flowlink->data().to);
			views::GenericNode *n1 = nullptr;
			views::GenericNode *n2 = nullptr;
			for (auto node : nodes)
			{
				if (n1 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == inputInstruction)
				{
					n1 = node;
				}
				else if (n2 == nullptr && qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == outputInstruction)
				{
					n2 = node;
				}
				if (n1 && n2)
					break;
			}
			if (!n1 || !n2) return;
			n1->createFlowLink(flowlink, n2);
		}

        /*
         * Link entry point
         */
        if (entryInstr != nullptr)
        {
            for (auto node : nodes)
            {
                if (qvariant_cast<models::gui::Instruction*>(node->property("instruction_model")) == entryInstr)
                {
                    entryPointObj->createFlowLink(new models::gui::FlowLink(), node);
                    break;
                }
            }
        }
    }

    QSettings *Editor::settings()
    {
        return m_settings;
    }

    void Editor::registerSettings(QSettings *settings)
    {
        m_settings = settings;
    }

    bool Editor::isNewVersionAvailable() const
    {
        return App::currentInstance()->isNewVersionAvailable();
    }

    qreal Editor::getSettingNumber(const QString &path)
    {
        return App::currentInstance()->getSettingNumber(path);
    }

	PropertyPanelProperties::PropertyPanelProperties(QObject *parent) : QObject(parent)
	{
		QMetaEnum metaEnum = QMetaEnum::fromType<core::VISIBILITY>();
		for (auto i = 0; i < metaEnum.keyCount(); i++)
		{
			m_visibility.append(metaEnum.key(i));
		}
		metaEnum = QMetaEnum::fromType<core::ENTITY>();
		for (auto i = 1; i < metaEnum.keyCount(); i++)
		{
			m_entityType.append(metaEnum.key(i));
		}
	}

	const QStringList &PropertyPanelProperties::visibility() const
	{
		return m_visibility;
	}

	const QStringList& PropertyPanelProperties::entityType() const
	{
		return m_entityType;
	}
}
