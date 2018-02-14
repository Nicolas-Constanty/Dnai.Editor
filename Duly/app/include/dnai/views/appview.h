#ifndef APPVIEW_H
#define APPVIEW_H
#include <QObject>

namespace dnai
{
	namespace views
	{
		class AppView : public QObject
		{
			Q_OBJECT
		public:
			explicit AppView(QObject* parent = nullptr);
		};
	}
}

#endif // APPVIEW_H
