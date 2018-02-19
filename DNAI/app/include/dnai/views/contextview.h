#ifndef CONTEXTVIEW_H
#define CONTEXTVIEW_H

#include <QQuickItem>

namespace dnai
{
	namespace views
	{
        class ContextView : public QQuickItem
		{
			Q_OBJECT
		public:
            explicit ContextView(QQuickItem *parent = nullptr);
            explicit ContextView(const QString &qmlview, QQuickItem *parent = nullptr);
            Q_INVOKABLE QQuickItem *getView() const;
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
