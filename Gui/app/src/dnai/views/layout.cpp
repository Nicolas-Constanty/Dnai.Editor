#include "dnai/views/layout.h"
#include "dnai/app.h"

dnai::views::Layout::Layout(QQuickItem* parent) : QQuickItem(parent), m_context(nullptr)
{
//	const auto app = App::currentInstance();
//	if (app->appView() != nullptr && app->appView()->layout() == nullptr)
//        app->appView()->setLayout(this);
}

dnai::views::Layout::~Layout()
{
    delete m_context;
    auto map = m_panels.toStdMap();
    map.erase(map.begin(), map.end());
    qDebug() << "~" << "Layout";
}

void dnai::views::Layout::setContextView(ContextView* ctxView)
{
	if (ctxView == m_context)
		return;
	m_context = ctxView;
    contextViewChanged(m_context);
}

dnai::views::ContextView* dnai::views::Layout::contextView() const
{
	return m_context;
}

QQuickItem* dnai::views::Layout::getPanel(const QString& name)
{
	if (m_panels.contains(name))
		return m_panels[name];
	return nullptr;
}

void dnai::views::Layout::addPanels(const QString& name, QQuickItem* item)
{
	m_panels[name] = item;
}
