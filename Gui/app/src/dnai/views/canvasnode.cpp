#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>
#include <QtMath>
#include <algorithm>

#include "dnai/app.h"
#include "dnai/views/canvasnode.h"
#include "dnai/views/genericnode.h"
#include "dnai/commands/movecanvascommand.h"
#include "dnai/commands/commandmanager.h"
#include "dnai/commands/zoomcanvascommand.h"

namespace dnai
{
	namespace views
	{
		CanvasNode::CanvasNode(QQuickItem *parent)
			: QQuickItem(parent)
			, m_gridStep(15)
			, m_accentGridStep(150)
			, m_backgroundColor(Qt::transparent)
		{
			m_content = new QQuickItem(this);
			setFlag(ItemHasContents, true);
			setAcceptHoverEvents(true);
            setAcceptedMouseButtons(Qt::AllButtons);
            setFlag(ItemAcceptsInputMethod, true);
		}

		void CanvasNode::createGrid()
		{
			m_lines.clear();
			const auto drawGrid = [&](double gridStep, int lineWidth, const QColor &color)
			{
				gridStep *= m_content->scale();
                lineWidth *= m_content->scale();

                const auto h = height();
                const auto w = width();
                const auto offsetX = m_gridOffset.x();
                const auto offsetY = m_gridOffset.y();
				// vertical lines
                for (auto xi = 0; xi < w - offsetX; xi += gridStep)
                {
                    const auto x = xi + offsetX;
                    if (x < 0)
                        continue;
                    if (xi == 0 && offsetX > 0)
                    {
                        auto xBack = x - gridStep;
                        while (xBack > 0) {
                            m_lines.push_back(Line::CreateRawLine(QPointF(xBack, 0), QPointF(xBack, h), lineWidth, color));
                            xBack -= gridStep;
                        }
                    }
                    m_lines.push_back(Line::CreateRawLine(QPointF(x, 0), QPointF(x, h), lineWidth, color));
				}

				// horizontal lines
                for (auto yi = 0; yi < h - offsetY; yi += gridStep)
                {
                    const auto y =  yi + offsetY;
                    if (y < 0)
                        continue;
                    if (yi == 0 && offsetY > 0)
                    {
                        auto yBack = y - gridStep;
                        while (yBack > 0) {
                            m_lines.push_back(Line::CreateRawLine(QPointF(0, yBack), QPointF(w, yBack), lineWidth, color));
                            yBack -= gridStep;
                        }
                    }
                    m_lines.push_back(Line::CreateRawLine(QPointF(0, y), QPointF(w, y), lineWidth, color));
                }
			};
			drawGrid(m_gridStep, 1, m_gridColor);

			drawGrid(m_accentGridStep, 2, m_accentGridColor);

		}

		void CanvasNode::mousePressEvent(QMouseEvent* event)
		{
            m_offset = event->pos();
			m_totalOffset = QPointF(0,0);
            GenericNode::resetSelected();
			if (event->button() == Qt::RightButton)
			{
				m_mousePosition = event->pos();
				qDebug() << "Mouse position :" << m_mousePosition;
				setContextMenu(!m_contextMenu);
			}
		}

		void CanvasNode::mouseReleaseEvent(QMouseEvent* event)
		{
			if (m_hasMoved)
            {
				m_hasMoved = false;
				const auto c = new commands::MoveCanvasCommand(this, event->pos() - m_offset, true);
				commands::CommandManager::Instance()->registerCommand(c);
				commands::CommandManager::Instance()->execAll();
			}
			m_hasMoved = false;
		}

		void CanvasNode::mouseMoveEvent(QMouseEvent* event)
        {
			const auto offset = event->pos() - m_offset;
			m_totalOffset += offset;
			const auto c = new commands::MoveCanvasCommand(this, offset, false);
			commands::CommandManager::Instance()->registerCommand(c);
			commands::CommandManager::Instance()->execAll();
			m_offset = event->pos();
			m_hasMoved = true;
		}

		void CanvasNode::moveCanvas(const QPointF &offset)
		{
			m_gridOffset = (m_gridOffset + offset);
			m_gridOffset.setX(static_cast<int>(m_gridOffset.x()) % (m_gridStep * 10));
            m_gridOffset.setY(static_cast<int>(m_gridOffset.y()) % (m_gridStep * 10));
			for (auto i = 0; i< m_content->childItems().size(); i++)
			{
                auto c = m_content->childItems().at(i);
				c->setPosition(c->position() + offset);
			}
			update();
		}

        void CanvasNode::wheelEvent(QWheelEvent *event)
        {
            if (event->modifiers() & Qt::ControlModifier)
            {
				const auto scale = m_content->scale() + 0.1 * event->angleDelta().y() / 120;
				if (scale == m_content->scale() || scale < 0.5f || scale > 2.1f)
					return;
				
                const auto w = width() / 2;
                const auto h = height() / 2;
                const auto offset = (scale < m_content->scale() ? 1 : -1) *
                    QPointF((event->pos().x() - w) / w,
                            (event->pos().y() - h) / h);
                const auto c = new commands::ZoomCanvasCommand(this, scale, offset);
				commands::CommandManager::Instance()->registerCommand(c);
				commands::CommandManager::Instance()->execAll();
            }
        }

		void CanvasNode::zoom(const double &scale, const QPointF &offset)
        {
			m_content->setScale(scale);
            const auto w = width();
            const auto h = height();
            auto rx = (h != 0) ? w / h : 1;
            auto ry = (w != 0) ? h / w : 1;
            if (rx > ry)
            {
                rx = 1;
                ry = ry / rx;
            }
            else
            {
                ry = 1;
                rx = rx / ry;
            }
            moveCanvas(QPointF(offset.x() * rx, offset.y() * ry) * 100);
		}

		CanvasNode::~CanvasNode()
		{
		}

		void CanvasNode::setAccentGridStep(int step)
		{
			if (step == m_accentGridStep)
				return;
			m_accentGridStep = step;
			emit accentGridStepChanged(step);
			update();
		}


		void CanvasNode::setGridStep(int step)
		{
			if (step == m_gridStep)
				return;
			m_gridStep = step;
			emit gridStepChanged(step);
			update();
		}

		void CanvasNode::setAccentGridColor(const QColor &color)
		{
			if (color == m_accentGridColor)
				return;
			m_accentGridColor = color;
			emit accentGridColorChanged(color);
			update();
		}


		void CanvasNode::setGridColor(const QColor &color)
		{
			if (color == m_gridColor)
				return;
			m_gridColor = color;
			emit gridColorChanged(color);
			update();
		}

		void CanvasNode::setBackgroundColor(const QColor &color)
		{
			if (color == m_backgroundColor)
				return;
			m_backgroundColor = color;
			emit backgroundColorChanged(color);
			update();
		}

		/*void CanvasNode::setScaleFactor(qreal scale)
		{
			if (scale == m_scaleFactor || scale < 0.5f || scale > 2.1f)
				return;
			m_scaleFactor = scale;
            emit scaleFactorChanged(scale);
			update();
		}*/

		void CanvasNode::setContent(QQuickItem* ct)
		{
			if (ct == m_content)
				return;
			m_content = ct;
			emit contentChanged(ct);
            update();
        }

		void CanvasNode::setContextMenu(bool b)
		{
			if (b == m_contextMenu)
				return;
			m_contextMenu = b;
			contextMenuChanged(b);
		}

		void CanvasNode::resetContent()
        {
            if (m_content &&  m_content->childItems().size() > 0)
            {
                while (!m_content->childItems().isEmpty()) {
                    delete m_content->childItems().first();
                }
                m_content->childItems().clear();
                zoom(1, QPoint(0,0));
            }
        }

		QSGNode *CanvasNode::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
		{
			auto n = static_cast<QSGSimpleRectNode *>(oldNode);
			m_origin = QPointF(width() / 2, height() / 2);
			if (!n) {
				n = new QSGSimpleRectNode();
			}
			n->setColor(m_backgroundColor);
			n->setRect(boundingRect());
			if (m_lines.size() > 0 && oldNode)
			{
				n->removeAllChildNodes();
				const auto deleteNodes = [&](QSGGeometryNode *o) { delete o; return true; };
				m_lines.remove_if(deleteNodes);
			}
			createGrid();
			const auto setParent = [&](QSGGeometryNode *o) { n->appendChildNode(o); };
			std::for_each(m_lines.begin(), m_lines.end(), setParent);
			return n;
		}
	}
}

