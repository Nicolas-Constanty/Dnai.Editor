#ifndef CONTEXTVIEW_H
#define CONTEXTVIEW_H

#include <QQuickItem>

namespace dnai
{
	namespace views
	{
		class ContextView : public QObject
		{
			Q_OBJECT
		public:
			explicit ContextView(QObject *parent = nullptr);
			explicit ContextView(const QString &qmlview, QObject *parent = nullptr);
			QQuickItem *getView() const;
			void addModel(QObject *model, const QString &name);
			QObject *getModel(const QString &name) const;

		private:
			void initView(const QString &path);
			void updateProgress(float percent);
			QQuickItem *m_view;
			float m_progess;
			QMap<QString, QObject *> m_models;
		};
	}
}

#endif // CONTEXTVIEW_H
