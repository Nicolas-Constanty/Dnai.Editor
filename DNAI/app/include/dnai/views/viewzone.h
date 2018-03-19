#ifndef DNAI_VIEWS_VIEWZONE_H
#define DNAI_VIEWS_VIEWZONE_H

#include <QQuickItem>
#include "dnai/interfaces/iviewzone.h"

namespace dnai
{
	namespace views
	{
		class ViewZone : public QQuickItem, public interfaces::IViewZone
		{
			Q_OBJECT
		public:
            ViewZone(QQuickItem *parent = nullptr);
			void serialize(QJsonObject& obj) const override;
		protected:
			void _deserialize(const QJsonObject& obj) override;

		public:
			void open() override;
			void close() override;
			void focusNext() override;
			void focusPrev() override;
			void addView(interfaces::IViewElement* view) override;
			const QList<interfaces::IViewElement*>& views() const override;
			void removeView() override;
			void split(SplitDirection dir) override;
			QList<interfaces::IViewElement*> m_views;
		};
	}
}

#endif
