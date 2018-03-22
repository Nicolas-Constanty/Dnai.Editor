#include "dnai/views/editorview.h"
#include "dnai/editor.h"

namespace dnai
{
	namespace views
	{
		EditorView::EditorView(QQuickItem* parent) : QQuickItem(parent), m_content(nullptr)
		{
			Editor::instance().registerEditorView(this);
		}

		void EditorView::setContent(QQuickItem *content)
		{
			if (content == m_content)
				return;
			m_content = content;
			m_content->setParentItem(this);
			emit contentChanged(m_content);
		}

		QQuickItem* EditorView::content() const
		{
			return m_content;
		}
	}
}
