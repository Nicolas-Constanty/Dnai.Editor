#include "dnai/views/layout.h"

dnai::views::Layout::Layout(QObject* parent) : QObject(parent), m_context(nullptr)
{
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
	if (m_panels.contains(name))
		return;
	m_panels[name] = item;
}
