#ifndef CONTEXTVIEW_H
#define CONTEXTVIEW_H

#include <QQuickItem>

namespace dnai
{
	namespace views
	{
		class ContextView : public QObject
		{
		public:
			explicit ContextView(const QString &qmlview, QObject *parent = nullptr);
			QQuickItem *getView() const;

		private:
			void initView(const QString &path);
			void updateProgress(float percent);
			QQuickItem *m_view;
			float m_progess;
		};
	}
}

#endif // CONTEXTVIEW_H
