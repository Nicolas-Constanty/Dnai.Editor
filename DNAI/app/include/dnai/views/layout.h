#ifndef LAYOUT_H
#define LAYOUT_H

#include "contextview.h"

namespace dnai
{
	namespace views
	{
		class Layout : public QQuickItem
		{
			Q_OBJECT
            Q_PROPERTY(ContextView * contextView READ contextView WRITE setContextView NOTIFY contextViewChanged)

        public:
			explicit Layout(QQuickItem *parent = nullptr);

		signals:
            void contextViewChanged(ContextView *ctxView);

		public:
            void setContextView(ContextView *ctxView);
			ContextView *contextView() const;
            Q_INVOKABLE QQuickItem *getPanel(const QString &name);
            Q_INVOKABLE void addPanels(const QString &name, QQuickItem *item);

		private:
			QMap<QString, QQuickItem *> m_panels;
			ContextView *m_context;
		};
	}
}

#endif // LAYOUT_H
