#include "dnai/views/appview.h"

dnai::views::AppView::AppView(QObject* parent) : QObject(parent), m_layout(nullptr)
{
}

dnai::views::AppView::~AppView()
{
    delete m_layout;
    qDebug() << "~" << "AppView";
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
