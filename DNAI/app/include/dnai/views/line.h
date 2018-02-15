#ifndef LINE_H
#define LINE_H

#include <QtQuick/QQuickItem>
#include <QtQuick/qsgnode.h>
#include <QColor>

namespace dnai
{
	namespace views
	{
		class Line : public QQuickItem
		{
			Q_OBJECT

			Q_PROPERTY(QPointF p1 READ p1 WRITE setP1 NOTIFY p1Changed)
			Q_PROPERTY(QPointF p2 READ p2 WRITE setP2 NOTIFY p2Changed)

			Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
			Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
		public:
			explicit Line(QQuickItem *parent = nullptr);
			Line(const QPointF &p1, const QPointF &p2, QQuickItem *parent = nullptr);
			Line(const QPointF &p1, const QPointF &p2, int lineWidth, QQuickItem *parent = nullptr);
			Line(const QPointF &p1, const QPointF &p2, int lineWidth, const QColor &color, QQuickItem *parent = nullptr);
			~Line();

			/**
			* \brief Override updatePaintNode and draw a Line
			* \return QSGNode *
			*/
			virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
			/**
			* \brief Static function Draw and return a Line
			* \param p1
			* \param p2
			* \param lineWidth
			* \param color
			* \return  QSGGeometryNode *
			*/
			static QSGGeometryNode *CreateRawLine(const QPointF &p1, const QPointF &p2, int lineWidth, const QColor &color);

		public:
			QPointF p1() const { return m_p1; }
			QPointF p2() const { return m_p2; }
			int lineWidth() const { return m_lineWidth; }
			QColor lineColor() const { return m_lineColor; }

		public:
			void setP1(const QPointF &p);
			void setP2(const QPointF &p);
			void setLineWidth(int lw);
			void setLineColor(const QColor &color);


		signals:
			void p1Changed(const QPointF &p);
			void p2Changed(const QPointF &p);
			void lineWidthChanged(int lw);
			void lineColorChanged(const QColor &color);

		private:
			QPointF m_p1;
			QPointF m_p2;
			int m_lineWidth;
			QColor m_lineColor;
		};
	}
}

#endif // LINE_H
