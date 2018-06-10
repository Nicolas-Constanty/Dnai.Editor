#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "dnai/link.h"
#include "dnai/views/io.h"

namespace dnai
{
	namespace views
	{
		BaseIo *Io::CurrentHover = nullptr;

		Io::Io(QQuickItem *parent) :
			LinkableBezierItem(parent)
			, m_nbSegments(32)
            , m_type(enums::IoTypeRessouce::IoType::Int)

		{
			Io::refreshBackendIo();
			setFlag(ItemHasContents, true);
			setAntialiasing(true);
		}

		Io::~Io()
		{
		}

		void Io::refreshBackendIo()
		{
		}

		QSGNode *Io::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
		{
			CustomShape::updatePaintNode(oldNode, data);
			const char r = m_fillColor.red();
			const char g = m_fillColor.green();
			const char b = m_fillColor.blue();
			const char alpha = m_fillColor.alpha();
			if (m_nbSegments != 0 && m_nbSegments % 2 != 0)
				++m_nbSegments;

			const char rb = m_borderColor.red();
			const char gb = m_borderColor.green();
			const char bb = m_borderColor.blue();
			const char alphab = m_borderColor.alpha();

			const auto aa = antialiasing();
			QSGGeometryNode *node;
			QSGGeometry *geometry;

			setWidth((m_radius + m_radius / 2.5f) * 2);
			setHeight((m_radius + m_radius / 2.5f) * 2);
			const uint nbVertices = (aa ? (m_borderWidth > 0 ? 8.0f * (m_nbSegments + 1) : 4 * (m_nbSegments + 1)) : (m_borderWidth > 0 ? 6 * (m_nbSegments + 1) : 2.5f * (m_nbSegments + 1))) + 1;
			if (!oldNode) {
				node = new QSGGeometryNode;
				geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertices);
				geometry->setLineWidth(1);
				geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
				node->setGeometry(geometry);
				node->setFlag(QSGNode::OwnsGeometry);
				auto material = new QSGVertexColorMaterial;
				material->setFlag(QSGMaterial::Blending);
				node->setMaterial(material);
				node->setFlag(QSGNode::OwnsMaterial);
			}
			else {
				node = static_cast<QSGGeometryNode *>(oldNode);
				geometry = node->geometry();
				geometry->allocate(nbVertices);
			}
			const auto cx = width() / 2;
			const auto cy = height() / 2;
			const auto a = float(2 * M_PI) / m_nbSegments;
			const qreal aaoffset = 1;
			const auto vertices = geometry->vertexDataAsColoredPoint2D();
			auto idx = -1;
			for (uint i = 0; i <= m_nbSegments; i++)
			{
				if (aa)
				{
					if (i % 2 == 0)
					{
						vertices[++idx].set(cx, cy, r, g, b, alpha);

						vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
						vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
						if (m_borderWidth > 0)
						{
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * i), cy + (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

							vertices[++idx].set(cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), 0, 0, 0, 0);
							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
						}
						else
						{
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * i), cy + (m_radius + aaoffset) * qFastSin(a * i), 0, 0, 0, 0);
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
						}
					}
					else
					{
						if (m_borderWidth > 0)
						{
							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);

							vertices[++idx].set(cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * i), cy + (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
						}
						else
						{
							vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
						}
						vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
						vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
					}
				}
				else
				{
					if (i % 2 == 0)
					{
						vertices[++idx].set(cx, cy, r, g, b, alpha);
						vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
						vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
						if (m_borderWidth > 0)
						{
							vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
						}
					}
					else
					{
						if (m_borderWidth > 0)
						{
							vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
							vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
							vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
						}
						vertices[++idx].set(cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
						vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
					}
				}
			}
			Q_ASSERT(static_cast<uint>(idx + 1) == nbVertices);
			node->markDirty(QSGNode::DirtyGeometry);
			return node;
		}

		void Io::setNbSegments(uint n)
		{
			if (n == m_nbSegments)
				return;
			m_nbSegments = n;
			emit nbSegmentsChanged(n);
			update();
		}

        void Io::setType(int type)
		{
			if (type == m_type)
				return;
			m_type = static_cast<enums::IoTypeRessouce::IoType>(type);
			refreshBackendIo();
			emit typeChanged(type);
			update();
		}

		QPointF Io::getCanvasPos() const
        {
            return QPointF(mapToItem(m_canvas->content(), QPoint(0,0)) +
                           QPointF(width() / 2, height() / 2));
		}

		GenericNode* Io::getNode() const
		{
			return dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
		}

		qreal Io::scaleFactor() const
		{
			return scale();
		}

		QPointF Io::scalePos() const
		{
			return realPos() * scale() + QPointF((width() * scale() - width()) / 2, (height() * scale() - height()) / 2);
		}

		QPointF Io::realPos() const
		{
			return (position() / scale()) + QPointF((width() / scale() - width()) / 2, (height() / scale() - height()) / 2);
		}

		void Io::setLink(Link *l)
		{
			resetShape();
			setFillColor(m_borderColor);
			if (l == nullptr) return;
			auto cs = dynamic_cast<Io *>(dynamic_cast<BaseIo*>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
			cs->setLink(nullptr);
			LinkableBezierItem::setLink(nullptr);
		}

		void Io::setHover()
		{
			if (m_status == LinkStatus::Hover) return;
			const auto c(m_borderColor);
			setBorderColor(m_fillColor);
			setFillColor(c);
			LinkableBezierItem::setHover();
		}
	}
}
