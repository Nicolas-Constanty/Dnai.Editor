#ifndef DECLARATIONVIEW_H
#define DECLARATIONVIEW_H

#include <QQuickItem>
#include "qmlresources/declarationtype.h"
#include "roundedrectangle.h"

namespace duly_gui
{
	namespace views
	{
		class DeclarationView : public QQuickItem
		{
			Q_OBJECT
            Q_PROPERTY(qmlresources::DeclarationTypeRessouce::DeclarationType type READ type WRITE setType NOTIFY typeChanged)
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
            Q_PROPERTY(qreal xPos READ xPos WRITE setXPos NOTIFY xPosChanged)
            Q_PROPERTY(qreal yPos READ yPos WRITE setYPos NOTIFY yPosChanged)
            Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
            Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
            Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
            Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)

		public:
			explicit DeclarationView(QQuickItem *parent = nullptr);

		signals:
            void typeChanged(const qmlresources::DeclarationTypeRessouce::DeclarationType type);
			void nameChanged(const QString &name);
			void descriptionChanged(const QString &name);
			void xPosChanged(const qreal x);
			void yPosChanged(const qreal y);
			void radiusChanged(const qreal radius);
			void colorChanged(const QColor &color);
			void borderColorChanged(const QColor &color);
			void borderWidthChanged(const qreal width);

		public:
            void setType(const qmlresources::DeclarationTypeRessouce::DeclarationType type);
			void setName(const QString &name);
			void setDescription(const QString &name);
			void setXPos(const qreal x);
			void setYPos(const qreal y);
			void setRadius(const qreal radius);
			void setColor(const QColor &color);
			void setBorderColor(const QColor &color);
			void setBorderWidth(const qreal width);

		public:
            qmlresources::DeclarationTypeRessouce::DeclarationType type() const { return m_type; }
            const QString &name() const { return m_name; }
			const QString &description() const { return m_description; }
            qreal xPos() const { return m_xPos; }
            qreal yPos() const { return m_yPos; }
            qreal radius() const { return m_radius; }
            const QColor &color() const { return  m_color; }
            const QColor &borderColor() const { return m_borderColor; }
            qreal borderWidth() const { return m_borderWidth; }
			//RoundedRectangle *view() const { return m_view; }

		private:
            qmlresources::DeclarationTypeRessouce::DeclarationType m_type;
			QString m_name;
			QString m_description;
			qreal m_xPos;
			qreal m_yPos;
			qreal m_radius;
			QColor m_color;
			QColor m_borderColor;
			qreal m_borderWidth;
			//RoundedRectangle* m_view;
		};
		}
		}

#endif // DECLARATIONVIEW_H
