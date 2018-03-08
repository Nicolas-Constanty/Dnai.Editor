#ifndef BORDERLESS_WINDOW_H
#define BORDERLESS_WINDOW_H

#include <QQuickWindow>

namespace dnai
{
	namespace views
    {
		class BorderlessWindow : public QQuickWindow
		{
            Q_OBJECT
        public:
			explicit BorderlessWindow(QWindow *parent = nullptr);
			explicit BorderlessWindow(QQuickRenderControl *renderControl);
            virtual ~BorderlessWindow();

		private:
            void init();
		};
	}
}

#endif //BORDERLESS_WINDOW_H
