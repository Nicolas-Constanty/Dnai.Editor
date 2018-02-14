#include <QSGSimpleRectNode>

#include "dnai/views/declarationview.h"
#include "dnai/views/roundedrectangle.h"

namespace dnai
{
	namespace views
	{
		DeclarationView::DeclarationView(QQuickItem* parent) : QQuickItem(parent)
			, m_xPos(0)
			, m_yPos(0)
			, m_radius(0)
			, m_borderWidth(0)
		{
			//m_view = new RoundedRectangle(this);
		}

        void  DeclarationView::setType(const qmlresources::DeclarationTypeRessouce::DeclarationType type)
		{
			if (type == m_type)
				return;
			m_type = type;
			emit typeChanged(type);
		}

        void DeclarationView::setName(const QString& name)
		{
			if (name == m_name)
				return;
			m_name = name;
			emit nameChanged(name);
		}

        void DeclarationView::setDescription(const QString& name)
		{
			if (name == m_description)
				return;
			m_description = name;
			emit descriptionChanged(name);
		}

        void DeclarationView::setXPos(const qreal x)
		{
			if (x == m_xPos)
				return;
			m_xPos = x;
			emit xPosChanged(x);
		}

        void DeclarationView::setYPos(const qreal y)
		{
			if (y == m_yPos)
				return;
			m_yPos = y;
			emit yPosChanged(y);
		}

        void DeclarationView::setRadius(const qreal radius)
		{
			if (radius == m_radius)
				return;
			m_radius = radius;
			emit radiusChanged(radius);
		}

        void DeclarationView::setColor(const QColor& color)
		{
			if (color == m_color)
				return;
			m_color = color;
			emit colorChanged(color);
		}

        void DeclarationView::setBorderColor(const QColor& color)
		{
			if (color == m_borderColor)
				return;
			m_borderColor = color;
			emit borderColorChanged(color);
		}

        void DeclarationView::setBorderWidth(const qreal width)
		{
			if (width == m_borderWidth)
				return;
			m_borderWidth = width;
			emit borderWidthChanged(width);
		}
	}
}
