#include "views/declarationcanvas.h"
#include <QQmlApplicationEngine>
#include "dulyapp.h"
#include "qmlresources/declarationtype.h"

namespace duly_gui
{
	namespace views
	{
        QList<QQmlComponent *> DeclarationCanvas::components;
		DeclarationCanvas::DeclarationCanvas(QQuickItem* parent) : DulyCanvas(parent)
		{

        }

		void DeclarationCanvas::CreateClass(const models::Class* cl, const bool recursif)
		{
            if (components.size() == 0)
                initComponents();
            if (!recursif)
            {
                auto obj = static_cast<QQuickItem *>(components[0]->create());
                obj->setParentItem(DulyApp::currentCanvasInstance()->content());

                const auto app = static_cast<DulyApp *>(DulyApp::instance());
                const auto sets = app->settings()->style();
                obj->setProperty("type", qmlresources::DeclarationTypeRessouce::DeclarationType::Class);
                obj->setProperty("width", sets->declarationView()->itemSize());
                obj->setProperty("height", sets->declarationView()->itemSize());
                obj->setProperty("name", cl->name());
                obj->setProperty("description", cl->description());
                obj->setProperty("xPos", cl->position().x());
                obj->setProperty("yPos", cl->position().y());
                obj->setProperty("radius", sets->declarationView()->declClass()->radius());
                obj->setProperty("color", sets->declarationView()->declClass()->background());
                obj->setProperty("borderColor", sets->declarationView()->declClass()->border()->color());
                obj->setProperty("borderWidth", sets->declarationView()->declClass()->border()->width());
            }


			if (recursif)
			{
                const auto functions = cl->functions();
                for (auto i = 0; i < functions.size(); i++)
                {
                    CreateFunction(functions[i]);
                }
				const auto variables = cl->attributes();
				for (auto i = 0; i < variables.size(); i++)
				{
					CreateVariable(variables[i]);
				}
			}
		}

		void DeclarationCanvas::CreateContext(const models::Context* cl, const bool recursif = true)
		{
            if (components.size() == 0)
                initComponents();
            if (!recursif)
            {
                auto obj = static_cast<QQuickItem *>(components[0]->create());
                obj->setParentItem(DulyApp::currentCanvasInstance()->content());

                const auto app = static_cast<DulyApp *>(DulyApp::instance());
                const auto sets = app->settings()->style();
                obj->setProperty("type", qmlresources::DeclarationTypeRessouce::DeclarationType::Context);
                obj->setProperty("width", sets->declarationView()->itemSize());
                obj->setProperty("height", sets->declarationView()->itemSize());
                obj->setProperty("name", cl->name());
                obj->setProperty("description", cl->description());
                obj->setProperty("xPos", cl->position().x());
                obj->setProperty("yPos", cl->position().y());
                obj->setProperty("radius", sets->declarationView()->declContext()->radius());
                obj->setProperty("color", sets->declarationView()->declContext()->background());
                obj->setProperty("borderColor", sets->declarationView()->declContext()->border()->color());
                obj->setProperty("borderWidth", sets->declarationView()->declContext()->border()->width());
            }


			if (recursif)
            {
                const auto context = cl->contexts();
                for (auto i = 0; i < context.size(); i++)
                {
                    CreateContext(context[i], false);
                }
				const auto classes = cl->classes();
				for (auto i = 0; i < classes.size(); i++)
				{
					CreateClass(classes[i], false);
				}
                const auto functions = cl->functions();
                for (auto i = 0; i < functions.size(); i++)
                {
                    CreateFunction(functions[i]);
                }
                const auto variables = cl->variables();
                for (auto i = 0; i < variables.size(); i++)
                {
                    CreateVariable(variables[i]);
                }
			}
		}

		void DeclarationCanvas::CreateFunction(const models::Function* cl)
		{
            if (components.size() == 0)
                initComponents();
			auto obj = static_cast<QQuickItem *>(components[0]->create());
            obj->setParentItem(DulyApp::currentCanvasInstance()->content());

			const auto app = static_cast<DulyApp *>(DulyApp::instance());
			const auto sets = app->settings()->style();
            obj->setProperty("type", qmlresources::DeclarationTypeRessouce::DeclarationType::Function);
			obj->setProperty("width", sets->declarationView()->itemSize());
			obj->setProperty("height", sets->declarationView()->itemSize());
			obj->setProperty("name", cl->name());
			obj->setProperty("description", cl->description());
            obj->setProperty("xPos", cl->position().x());
            obj->setProperty("yPos", cl->position().y());
			obj->setProperty("radius", sets->declarationView()->declFunction()->radius());
			obj->setProperty("color", sets->declarationView()->declFunction()->background());
			obj->setProperty("borderColor", sets->declarationView()->declFunction()->border()->color());
			obj->setProperty("borderWidth", sets->declarationView()->declFunction()->border()->width());

			const auto variables = cl->variables();
			for (auto i = 0; i < variables.size(); i++)
			{
				CreateVariable(variables[i]);
			}
		}

		void DeclarationCanvas::CreateVariable(const models::Variable* cl)
		{
            if (components.size() == 0)
                initComponents();
			auto obj = static_cast<QQuickItem *>(components[0]->create());
            obj->setParentItem(DulyApp::currentCanvasInstance()->content());

			const auto app = static_cast<DulyApp *>(DulyApp::instance());
			const auto sets = app->settings()->style();
            obj->setProperty("type", qmlresources::DeclarationTypeRessouce::DeclarationType::Variable);
			obj->setProperty("width", sets->declarationView()->itemSize());
			obj->setProperty("height", sets->declarationView()->itemSize());
			obj->setProperty("name", cl->name());
			obj->setProperty("description", cl->description());
            obj->setProperty("xPos", cl->position().x());
            obj->setProperty("yPos", cl->position().y());
			obj->setProperty("radius", sets->declarationView()->declVariable()->radius());
			obj->setProperty("color", sets->declarationView()->declVariable()->background());
			obj->setProperty("borderColor", sets->declarationView()->declVariable()->border()->color());
			obj->setProperty("borderWidth", sets->declarationView()->declVariable()->border()->width());
		}

		void DeclarationCanvas::initComponents()
		{
			registerComponent("qrc:/resources/Components/DeclarationView.qml");
		}

		void DeclarationCanvas::registerComponent(const QString &path)
		{
			const auto p = QUrl(path);
			const auto app = static_cast<DulyApp *>(DulyApp::instance());
			const auto component = new QQmlComponent(app->engine(), p);
			components.append(component);
		}
	}
}
