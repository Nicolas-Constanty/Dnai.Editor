#include "dnai/views/borderlesswindow.h"
#include <QEvent>
#include <QFocusEvent>
#include <qt_windows.h>
#include <QWindow>

namespace dnai
{
	namespace views
    {
        BorderlessWindow::BorderlessWindow(QWindow *parent) : QQuickWindow(parent)
		{
            init();
        }

        BorderlessWindow::BorderlessWindow(QQuickRenderControl* renderControl) : QQuickWindow(renderControl)
		{
			init();
		}

		BorderlessWindow::~BorderlessWindow()
        {

        }

		void BorderlessWindow::init()
		{
			setFlag(Qt::FramelessWindowHint, true);
		}
	}
}
