#ifndef CANVASNODE_H
#define CANVASNODE_H

#include <list>

#include "line.h"
#include "dnai/focusmanager.h"

namespace dnai
{
	namespace views
	{
		class CanvasNode : public QQuickItem
		{
			Q_OBJECT

        public:
			Q_PROPERTY(int gridStep READ gridStep WRITE setGridStep NOTIFY gridStepChanged)
			Q_PROPERTY(int accentGridStep READ accentGridStep WRITE setAccentGridStep NOTIFY accentGridStepChanged)

			Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
			Q_PROPERTY(QColor accentGridColor READ accentGridColor WRITE setAccentGridColor NOTIFY accentGridColorChanged)
			Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

			Q_PROPERTY(QQuickItem *content READ content WRITE setContent NOTIFY contentChanged)
            Q_PROPERTY(bool contextMenu READ contextMenu WRITE setContextMenu NOTIFY contextMenuChanged)
			Q_PROPERTY(QPoint mousePosition READ mousePosition CONSTANT)

			explicit CanvasNode(QQuickItem *parent = nullptr);
			~CanvasNode();

			/**
			* \brief return the focusManager
			* \return FocusManager &
			*/
			FocusManager &focusManager() { return m_focusManager; }

			/**
			* \brief Override updatePaintNode and draw a beautifull canvas
			* \return QSGNode *
			*/
			virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
			void moveCanvas(const QPointF& pos);
			void zoom(const double& scale, const QPointF& offset);

		public:
			int gridStep() const { return m_gridStep; }
			int accentGridStep() const { return m_accentGridStep; }

			QColor gridColor() const { return m_gridColor; }
			QColor accentGridColor() const { return m_accentGridColor; }
			QColor backgroundColor() const { return m_backgroundColor; }
			const QPointF &totalOffset() const { return m_totalOffset; }
			const QPointF &origin() const { return m_origin; }
			QQuickItem *content() const { return m_content; }
            bool contextMenu() const { return m_contextMenu; }
			const QPoint &mousePosition() const { return m_mousePosition; }
            QQuickItem *entry() const { return m_entry; }

		public:
			void setGridStep(int step);
			void setAccentGridStep(int step);
			void setGridColor(const QColor &color);
			void setAccentGridColor(const QColor &color);
			void setBackgroundColor(const QColor & color);
            void setContent(QQuickItem *ct);
			void setContextMenu(bool b);
            void resetContent();
            void registerEntry(QQuickItem *entry);


		signals:
			void gridStepChanged(int step);
			void accentGridStepChanged(int step);
			void gridColorChanged(const QColor &color);
			void accentGridColorChanged(const QColor &color);
			void backgroundColorChanged(const QColor &color);
			void contentChanged(QQuickItem *ct);
			void contextMenuChanged(bool b);


		private:
			int m_gridStep;
			int m_accentGridStep;

			QColor m_gridColor;
			QColor m_accentGridColor;
			QColor m_backgroundColor;
			bool m_hasMoved;
			QPointF m_totalOffset;
			bool m_contextMenu;
			QPoint m_mousePosition;

		private:
			void createGrid();
			FocusManager m_focusManager;
			std::list<QSGGeometryNode *> m_lines;
			QPointF	m_offset;
			QPointF	m_gridOffset;
			QPointF m_origin;
            QQuickItem *m_content;
            QQuickItem *m_entry = nullptr;

		protected:
			void mousePressEvent(QMouseEvent* event) override;
			void mouseReleaseEvent(QMouseEvent* event) override;
			void mouseMoveEvent(QMouseEvent* event) override;
            void wheelEvent(QWheelEvent *event) override;
		};
	}
}

#endif // CANVASNODE_H
