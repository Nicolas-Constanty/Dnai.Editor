#include <tuple>

#include <QObject>
#include <QQmlProperty>
#include <QQuickView>
#include <QJsonDocument>
#include <QDir>

#ifdef _WIN32
# include <quazip.h>
# include <quazipfile.h>
#endif

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
    Editor *Editor::m_instance = nullptr;

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
       App::currentInstance().load();

       QObject::connect(&dnai::gcore::HandlerManager::Instance().Function(), SIGNAL(addInstructionError(quint32,quint32,QList<quint32>,QString)),
                        this, SLOT(onAddInstructionError(quint32,quint32,QList<quint32>,QString)));

       loadContextMenuModel();
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

    bool Editor::packSolution()
    {
        QString packPath = m_solution->path() + "/" + m_solution->name() + ".dnaipackage";
        QDir solutionDir(m_solution->path());

        #ifdef _WIN32
        QuaZip  archive(packPath);

        if (!archive.open(QuaZip::mdCreate))
        {
            notifyError("Couldn't create package: " + packPath);
            return false;
        }

        for (QFileInfo fileInfo : solutionDir.entryInfoList(QDir::Files))
        {
            QString fileName = fileInfo.fileName();

            if (fileInfo.suffix() == "dnaipackage")
            {
                continue;
            }

            QString filePath = fileInfo.absoluteFilePath();

            QFile input(filePath);
            QuaZipFile zipFile(&archive);
            QuaZipNewInfo info(fileName, filePath);

            if (!input.open(QIODevice::ReadOnly))
            {
                archive.close();
                notifyError("Unable to open file " + fileName + ": " + input.errorString());
                return false;
            }

            if (!zipFile.open(QIODevice::WriteOnly, info))
            {
                input.close();
                archive.close();
                notifyError("Unable to zip file " + fileName + ": " + zipFile.errorString());
                return false;
            }

            zipFile.write(input.readAll());

            zipFile.close();
            input.close();
        }

        archive.close();
        #else
        #endif

        return true;
    }

    QUrl Editor::unpackSolution(QUrl packageUrl)
    {
        QString packagePath = packageUrl.toLocalFile();
        QString solutionPath;

        #ifdef _WIN32
        QuaZip archive(packagePath);

        qDebug() << "==Editor== Unpacking package " << packagePath;

        if (!archive.open(QuaZip::mdUnzip))
        {
            notifyError("Unable to open package: " + packagePath);
            return QString();
        }

        QFileInfo packageInfo(packagePath);
        QString projectDirPath = packageInfo.absolutePath() + "/" + packageInfo.baseName();
        QDir projectDirectory(projectDirPath);

        if (!projectDirectory.exists() && !projectDirectory.mkpath(projectDirPath))
        {
            notifyError("Unable to create directory entry: " + projectDirPath);
            return QString();
        }

        QuaZipFileInfo currInfo;

        archive.goToFirstFile();
        while (archive.getCurrentFileInfo(&currInfo))
        {
            QString outFilePath = projectDirPath + "/" + currInfo.name;
            QFile output(outFilePath);
            QuaZipFile zipFile(&archive);

            if (!output.open(QIODevice::WriteOnly))
            {
                notifyError("Unable to create file " + outFilePath + ": " + output.errorString());
                return QString();
            }

            if (!zipFile.open(QIODevice::ReadOnly))
            {
                notifyError("Unable to read packed file: " + currInfo.name);
                return QString();
            }

            output.write(zipFile.readAll());

            output.close();
            zipFile.close();

            if (QFileInfo(outFilePath).suffix() == "dnaisolution")
            {
                solutionPath = outFilePath;
            }

            archive.goToNextFile();
        }

        qDebug() << "==Editor== Project unpacked at " << solutionPath;

        archive.close();
        #else



        #endif

        return QUrl::fromLocalFile(solutionPath);
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
        if (m_instance == nullptr)
            m_instance = new Editor();
        return *m_instance;
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

    void Editor::loadContextMenuModel()
    {
        QFile file(":resources/Nodes/Operators.json");

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open file: " << file.errorString();
            return;
        }

        const QByteArray data = file.readAll();

        try {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(data, &err);

            if (doc.isNull() || doc.isEmpty())
            {
                qWarning() << "==Editor== Unable to parse default nodes for context menu model: " << err.errorString();
            }

            const QJsonObject obj(doc.object());

            m_contextMenuModel = new dnai::models::ContextMenuModel(obj);
        }
        catch (std::exception &e) {
            Q_UNUSED(e)
                exceptions::ExceptionManager::throwException(exceptions::GuiExeption("Error : Corrupted Solution file"));
            qWarning("Couldn't parse file.");
        }
        file.close();
        m_contextMenuModel->setup();
    }

    dnai::models::ContextMenuModel* Editor::contextMenuModel() const
    {
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
        /*const auto function = dynamic_cast<models::gui::declarable::Function *>(entity->guiModel());
		if (function == nullptr) return;
        m_contextMenuModel->hideParameters();
        m_contextMenuModel->hideReturns();
		for (auto param : function->inputs())
		{
            m_contextMenuModel->displayParameter(param);
		}
		for (auto ret : function->outputs())
		{
            m_contextMenuModel->displayReturn(ret);
        }
        emit contextMenuModelChanged(m_contextMenuModel);*/
	}

	void Editor::registerEditorView(views::EditorView* view)
	{
		m_editorView = view;
    }

    Session *Editor::session() const
    {
        return &App::currentInstance().session();
    }

    void Editor::setAppName(const QString &name)
    {
        m_appname = name;
    }

    void Editor::setSolutionName(const QString &name)
    {
        m_solutionName = name;
    }

    ml::MlHandler *Editor::mlHandler()
    {
        return &m_mlHandler;
    }

    QQuickItem * Editor::createNodeQMLComponent(models::Entity *func, models::gui::Instruction *instruction, QQuickItem *parent) const
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
        model.write(QVariant::fromValue(contextMenuModel()->instructions()[instruction->nodeMenuPath()]));
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

    void Editor::setAsEntryPoint(views::GenericNode *instruction, views::GenericNode *entry)
    {
        entry->createFlowLink(new models::gui::FlowLink(), instruction);
    }

    void Editor::createFlowLink(dnai::views::GenericNode *from, dnai::views::GenericNode *to, dnai::models::Entity *func, dnai::models::gui::Instruction *fromIns, qint32 outpin, dnai::models::gui::Instruction *toIns) const
    {
        models::Function *data = func->guiModel<models::Function>();
        models::gui::FlowLink *link = data->findFlowLink(fromIns->guiUuid(), outpin, toIns->guiUuid());

        if (link == nullptr)
            throw std::runtime_error("No such link for outpin " + std::to_string(outpin) + " of instrution " + std::to_string(fromIns->Uid()));
        from->createFlowLink(link, to);
    }

    void Editor::removeFlowLink(views::GenericNode *instruction, qint32 outpin) const
    {
        instruction->unlinkFlow(outpin);
    }

    void Editor::createIOLink(views::GenericNode *from, views::GenericNode *to, dnai::models::Entity *func, dnai::models::gui::Instruction *instr, QString input) const
    {
        models::Function *data = func->guiModel<models::Function>();
        dnai::models::gui::IoLink   *link = data->findIOLink(instr->guiUuid(), input);

        if (link == nullptr)
            throw std::runtime_error("No such link for input " + input.toStdString() + " of instrution " + std::to_string(instr->Uid()));
        from->createLink(link, to);
    }

    void Editor::removeIOLink(views::GenericNode *instruction, dnai::models::gui::Instruction *instr, QString input) const
    {
        int index = 0;

        for (models::gui::Input *curr : instr->inputs())
        {
            if (curr->name() == input)
            {
                instruction->unlinkIo(index);
                return;
            }
            ++index;
        }
    }

    void Editor::finishInstructionBuilding(models::Entity *func, models::gui::Instruction *instruction)
    {
        models::ContextMenuItem *node;

        if (!m_pendingInstruction.empty())
        {
            quint32 x, y;

            std::tie(node, x, y) = m_pendingInstruction.front();
            instruction->setX(x);
            instruction->setY(y);
            instruction->setNodeMenuPath(node->fullPath());
            m_pendingInstruction.pop();
        }
        else
        {
            node = contextMenuModel()->instructions()[instruction->nodeMenuPath()];
        }

        if (node == nullptr)
        {
            qWarning() << "==Editor== No such node in context menu: " << instruction->nodeMenuPath();
            return;
        }

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
                toadd->setVarType(QUuid::fromString(node->getInput(curr)));
                inputs.append(toadd);
                qDebug() << "==Editor== Set " << curr << " input type to " << toadd->varType().toString();
            }

            instruction->setInputs(inputs);
        }

        for (models::gui::Input *curr : instruction->inputs())
        {
            if (!curr->value().isEmpty())
                dnai::gcore::HandlerManager::Instance().function()->instruction()->setInputValue(func->id(), instruction->Uid(), curr->name(), curr->value(), false);
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
                toadd->setVarType(QUuid::fromString(node->getOutput(curr)));
                outputs.append(toadd);
                qDebug() << "==Editor== Set " << curr << " output type to " << toadd->varType().toString();
            }

            instruction->setOutputs(outputs);
        }
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
        App::currentInstance().versionsUpdater();
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
                nodes.append(dynamic_cast<views::GenericNode *>(createNodeQMLComponent(entity, instruction, canvas->content())));
            }
            else
            {
                qDebug() << instructionsMap;
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

            if (inputInstruction == nullptr || outputInstruction == nullptr)
                continue;

            qDebug() << "==Editor== Link input instruction(" << inputInstruction->guiUuid() << ") => " << inputInstruction->nodeMenuPath();
            qDebug() << "==Editor== Link output instruction(" << outputInstruction->guiUuid() << ") => " << outputInstruction->nodeMenuPath();

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

            if (inputInstruction == nullptr || outputInstruction == nullptr)
                continue;

            qDebug() << "==Editor== Link input instruction(" << inputInstruction->guiUuid() << ") => " << inputInstruction->nodeMenuPath();
            qDebug() << "==Editor== Link output instruction(" << outputInstruction->guiUuid() << ") => " << outputInstruction->nodeMenuPath();

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
        return App::currentInstance().isNewVersionAvailable();
    }

    qreal Editor::getSettingNumber(const QString &path)
    {
        return App::currentInstance().getSettingNumber(path);
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
