#include "dnai/views/customshape.h"

namespace dnai
{
	namespace views
	{
		CustomShape::CustomShape(QQuickItem * parent) :
			QQuickItem(parent)
			, m_radius(-1)
			, m_borderWidth(-1)
			, m_fillColor(QColor(0, 0, 0, 0))
			, m_borderColor(QColor(0, 0, 0, 0))
			, m_saveRadius(-1)
			, m_saveBorderWidth(-1)
			, m_saveFillColor(QColor(0, 0, 0, 0))
			, m_saveBorderColor(QColor(0, 0, 0, 0))
			, m_savePos(-100000, -100000)
		{
			setFlag(ItemHasContents, true);
		}

		void CustomShape::setRadius(qreal radius)
		{
			if (radius == m_radius)
				return;
			m_radius = radius;
			emit radiusChanged(radius);
			update();
		}

		void CustomShape::setBorderWidth(qreal w)
		{
			if (w == m_borderWidth)
				return;
			m_borderWidth = w;
			emit borderWidthChanged(w);
			update();
		}

		void CustomShape::setFillColor(const QColor &color)
		{
			if (color == m_fillColor)
				return;
			m_fillColor = color;
			emit fillColorChanged(color);
			update();
		}

		void CustomShape::setBorderColor(const QColor &color)
		{
			if (color == m_borderColor)
				return;
			m_borderColor = color;
			emit borderColorChanged(color);
			update();
		}

		void CustomShape::resetRadius()
		{
			if (m_saveRadius != -1)
				setRadius(m_saveRadius);
		}
		void CustomShape::resetBorderWidth()
		{
			if (m_saveBorderWidth != -1)
				setBorderWidth(m_saveBorderWidth);
		}
		void CustomShape::resetBorderColor()
		{
			setBorderColor(m_saveBorderColor);
		}
		void CustomShape::resetFillColor()
		{
			setFillColor(m_saveFillColor);
		}

		void CustomShape::resetPos()
		{
			setPosition(m_savePos);
		}

		void CustomShape::resetShape()
		{
			resetRadius();
			resetBorderWidth();
			resetBorderColor();
			resetFillColor();
			resetPos();
		}

		QSGNode *CustomShape::updatePaintNode(QSGNode *n, UpdatePaintNodeData *)
		{
			if (m_saveRadius == -1)
				m_saveRadius = m_radius;
			if (m_saveBorderWidth == -1)
				m_saveBorderWidth = m_borderWidth;
			if (m_saveFillColor == QColor(0, 0, 0, 0))
				m_saveFillColor = m_fillColor;
			if (m_saveBorderColor == QColor(0, 0, 0, 0))
			{
				m_saveBorderColor = m_borderColor;
			}
			if (m_savePos == QPointF(-100000, -100000))
				m_savePos = position();
			return n;
		}
	}
}
