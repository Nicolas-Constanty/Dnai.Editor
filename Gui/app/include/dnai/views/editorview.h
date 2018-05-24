#ifndef  DNAI_VIEWS_EDITOR_VIEW_H
#define DNAI_VIEWS_EDITOR_VIEW_H
#include <QQuickItem>

namespace dnai
{
	namespace views
	{
		class EditorView : public QQuickItem
		{
			Q_OBJECT
			Q_PROPERTY(QQuickItem *content READ content WRITE setContent NOTIFY contentChanged)
		public:
			explicit EditorView(QQuickItem *parent = nullptr);
			void setContent(QQuickItem *content);
			QQuickItem *content() const;

		signals:
			void contentChanged(QQuickItem *content);

		private:
			QQuickItem *m_content;
		};
	}
}

#endif //DNAI_VIEWS_EDITOR_VIEW_H