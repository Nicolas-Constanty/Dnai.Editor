#include "dnai/views/appview.h"

dnai::views::AppView::AppView(QObject* parent) : QObject(parent), m_layout(nullptr)
{
}

void dnai::views::AppView::setLayout(Layout* l)
{
	if (l == m_layout) return;
	m_layout = l;
	layoutChanged(l);
}

dnai::views::Layout* dnai::views::AppView::layout() const
{
	return m_layout;
}
