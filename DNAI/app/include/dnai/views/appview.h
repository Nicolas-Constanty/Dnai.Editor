#ifndef APPVIEW_H
#define APPVIEW_H
#include <QObject>

#include "layout.h"

namespace dnai
{
	namespace views
	{
		class AppView : public QObject
		{
			Q_OBJECT
            Q_PROPERTY(Layout *layout READ layout WRITE setLayout NOTIFY layoutChanged)
		public:
			explicit AppView(QObject* parent = nullptr);
            ~AppView();

        signals:
            void layoutChanged(Layout *l);

        public:
            void setLayout(Layout *l);
            Layout *layout() const;

        private:
            Layout *m_layout;
		};
	}
}

#endif // APPVIEW_H
