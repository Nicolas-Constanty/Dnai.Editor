#ifndef IOQUICKITEM_H
#define IOQUICKITEM_H

#include <QQuickItem>

namespace duly_gui
{
	class IoQuickItem : public QQuickItem
	{
		Q_OBJECT
	public:
		explicit IoQuickItem(QQuickItem *parent = nullptr);

	signals:

		public slots :
	};
}


#endif // IOQUICKITEM_H
