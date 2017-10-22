#ifndef CONSOLE_H
#define CONSOLE_H
#include <QQuickItem>

namespace duly_gui
{
	namespace views
	{
        class Console : public QQuickItem
		{
			Q_OBJECT
            Q_PROPERTY(QStringList text READ text WRITE setText NOTIFY textChanged)
		public:
            explicit Console(QQuickItem *parent = nullptr);
            const QStringList &text() const { return m_text; }
            void setText(const QStringList &text);
			void addText(const QString &text);

        signals:
            void textChanged(const QStringList &text);

		protected:
            QStringList m_text;

		};
	}
}

#endif // CONSOLE_H
