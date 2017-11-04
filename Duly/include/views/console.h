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
        public:
            enum ConsoleMode
            {
                Normal,
                Verbose
            };
            Q_ENUM(ConsoleMode)
            Q_PROPERTY(QStringList text READ text WRITE setText NOTIFY textChanged)
            Q_PROPERTY(ConsoleMode mode READ mode WRITE setMode NOTIFY modeChanged)

		public:
            explicit Console(QQuickItem *parent = nullptr);
            const QStringList &text() const { return m_text; }
            void setText(const QStringList &text);
            ConsoleMode mode() const { return m_mode; }
            void setMode(ConsoleMode mode);
			void addText(const QString &text);

        signals:
            void textChanged(const QStringList &text);
			void modeChanged(ConsoleMode mode);

		protected:
            QStringList m_text;
            ConsoleMode m_mode;

		};
	}
}

#endif // CONSOLE_H
