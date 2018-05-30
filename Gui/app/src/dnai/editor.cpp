#include <QQuickItem>
#include <QQmlProperty>
#include <QQuickView>
#include <QJsonArray>

#include "dnai/editor.h"
#include "dnai/solution.h"
#include "dnai/project.h"
#include "dnai/exceptions/notimplemented.h"
#include "dnai/exceptions/exceptionmanager.h"
#include "dnai/interfaces/iviewzone.h"
#include "dnai/app.h"
#include "dnai/views/canvasnode.h"

#include "dnai/core/handlermanager.h"

namespace dnai
{
	Editor &Editor::m_instance = *(new Editor());

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
                gcore::HandlerManager::Instance().Project().create(p);
	}

	void Editor::loadSolution(const QString& filename)
	{
		m_solution = new Solution();
		if (!filename.isEmpty())
            m_solution->load(filename);
    }

    void Editor::startApp()
    {
       App::currentInstance()->load();
    }

	void Editor::closeSolution()
	{
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

    void Editor::onBuildSuccess() {
        this->notifySuccess("Build succeeded !", [](){
        });
        //TODO REPLACE
        QFile file("D:\\EIP\\Core\\TestCommand\\bin\\Debug\\moreOrLess.dnai");

        file.copy("C:\\Users\\GasparQ\\Desktop\\Test\\moreOrLess.dnai");
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

	QQuickItem *Editor::selectedView() const
	{
		return m_seletedItem;
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

    models::BasicNodeModel *Editor::nodes() const
    {
        return App::currentInstance()->nodes();
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

	void Editor::registerEditorView(views::EditorView* view)
	{
		m_editorView = view;
    }

    Session *Editor::session() const
    {
        return &App::currentInstance()->session();
    }

    void Editor::createNode(models::Entity *entity, QObject *nodeModel, qint32 x, qint32 y) const
    {
		auto function = dynamic_cast<models::gui::declarable::Function *>(entity->guiModel());
		if (function == nullptr) return;
		auto instruction = new models::gui::Instruction();
		instruction->setX(x);
		instruction->setY(y);
		instruction->setInstructionId(nodeModel->property("instruction_id").toInt());
		function->addInstruction(instruction);
        const QString path = "qrc:/resources/Components/Node.qml";
        QQmlComponent component(App::getEngineInstance(), path);
        QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(App::getEngineInstance()->rootContext()));
        QQmlProperty model(obj, "model", App::getEngineInstance());
        model.write(QVariant::fromValue(App::currentInstance()->nodes()->createNode(static_cast<enums::QInstructionID::Instruction_ID>(instruction->instruction_id()))));
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
	    const auto canvas = dynamic_cast<views::CanvasNode *>(view);
        obj->setParentItem(canvas->content());
        component.completeCreate();
    }

    void Editor::checkVersion()
    {
        auto app = App::currentInstance();
        app->versionsUpdater();
      //  app->onNotifyVersionChanged();
    }

	models::EntityList *Editor::entities()
	{
		return models::Entity::m_entities;
	}

    void Editor::registerMainView(QObject *mainView) {
        m_mainView = static_cast<QQuickWindow*>(mainView);
    }

    void Editor::createSolution(const QString &name,
                                const QString &description,
                                const QString &path,
                                const QString &proj_name,
                                const QString &proj_desc)
    {
        const auto sol_path = path + "/" + name + ".dnaisolution";
        auto solution = new Solution(sol_path);
        solution->setName(name);
        solution->setDescription(description);
        auto p = new Project(path + "/" + proj_name + ".dnaiproject");
        p->setName(proj_name);
        p->setDescription(proj_desc);
        solution->addProject(p);
        solution->save();
        loadSolution(sol_path);
    }

    QQuickWindow *Editor::mainView()  {
        return m_mainView;
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
		const QString path = "qrc:/resources/Components/Node.qml";
		QQmlComponent component(App::getEngineInstance(), path);
		const auto canvas = dynamic_cast<views::CanvasNode *>(view);

		for (const auto instruction : function->instructions())
		{
			QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(App::getEngineInstance()->rootContext()));
			QQmlProperty model(obj, "model", App::getEngineInstance());
			model.write(QVariant::fromValue(App::currentInstance()->nodes()->createNode(static_cast<enums::QInstructionID::Instruction_ID>(instruction->instruction_id()))));
			obj->setParentItem(canvas->content());
			obj->setX(instruction->x());
			obj->setY(instruction->y());
			component.completeCreate();
		}
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

    const QStringList &PropertyPanelProperties::varType() const
	{
        return models::gui::declarable::Variable::getVariableList();
	}
}
