#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "views/roundedrectangle.h"

namespace duly_gui
{
	namespace views
	{
		RoundedRectangle::RoundedRectangle(QQuickItem *parent) :
			CustomShape(parent)
			, m_topLeft(true)
			, m_topRight(true)
			, m_bottomLeft(true)
			, m_bottomRight(true)
			, m_nbSegments(5)
		{
			setFlag(ItemHasContents, true);
		}

		void RoundedRectangle::setTopLeft(bool value)
		{
			if (value == m_topLeft)
				return;
			m_topLeft = value;
			emit topLeftChanged(value);
			update();
		}

		void RoundedRectangle::setTopRight(bool value)
		{
			if (value == m_topRight)
				return;
			m_topRight = value;
			emit topRightChanged(value);
			update();
		}

		void RoundedRectangle::setBottomLeft(bool value)
		{
			if (value == m_bottomLeft)
				return;
			m_bottomLeft = value;
			emit bottomLeftChanged(value);
			update();
		}

		void RoundedRectangle::setBottomRight(bool value)
		{
			if (value == m_bottomRight)
				return;
			m_bottomRight = value;
			emit bottomRightChanged(value);
			update();
		}

		void RoundedRectangle::setRoundedSegments(uint segments)
		{
			if (segments == m_nbSegments)
				return;
			m_nbSegments = segments;
			emit roundedSegmentsChanged(segments);
			update();
		}

		int RoundedRectangle::getNumberRoundedCorner() const
		{
			int count = 0;
			if (m_topLeft)
				++count;
			if (m_topRight)
				++count;
			if (m_bottomLeft)
				++count;
			if (m_bottomRight)
				++count;
			return count;
		}

		QSGNode *RoundedRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
		{
            CustomShape::updatePaintNode(oldNode, data);
			QSGGeometryNode *node;
			QSGGeometry *geometry;
			auto idx = -1;
            const auto aaoffset = 1;
			const auto h = (height() - m_radius * 2.f) / 2.f;
			const auto w = (width() - m_radius * 2.f) / 2.f;

            const auto r = m_fillColor.red() * m_fillColor.alphaF();
            const auto g = m_fillColor.green() * m_fillColor.alphaF();
            const auto b = m_fillColor.blue() * m_fillColor.alphaF();
            const auto alpha = m_fillColor.alpha();

            const uchar rb = m_borderColor.red() * m_borderColor.alphaF();
            const uchar gb = m_borderColor.green() * m_borderColor.alphaF();
            const uchar bb = m_borderColor.blue() * m_borderColor.alphaF();
            const uchar alphab = m_borderColor.alpha();

			const uchar ra = 0;
			const uchar ga = 0;
			const uchar ba = 0;
			const uchar alphaa = 0;

			const auto nCorner = getNumberRoundedCorner();
			const auto aa = antialiasing();
            const QPointF center(w + m_radius, h + m_radius);
            m_nbSegments += (m_nbSegments % 2 == 0) ? 0 : 1;
            const auto a = 0.5f * float(M_PI) / (m_nbSegments - 1);
			// Corners
			// Normal + AA + Border  (9 + 8) / 2 = 8.5f
			// Normal + AA           (5 + 3) / 2 = 4
			// Normal + Border       (7 + 5) / 2 = 6
			// Normal                (3 + 2) / 2 = 2.5f

			// Normal + AA + Border Total = (8.5 * (m_nbSegments -1)) * nCorner
			// Normal + AA          Total = (4 * (m_nbSegments -1)) * nCorner
			// Normal + Border      Total = (6 * (m_nbSegments -1)) * nCorner
			// Normal               Total = (2.5 * (m_nbSegments -1)) * nCorner

			// Normal + AA + Border 6 + 8 = 14
			// Normal + AA          6 + 3 = 9
			// Normal + Border      6 + 6 = 12
			// Normal               6

			// Normal + AA + Border Total = 14 * 4 - (4 - nCorner) * 2
			// Normal + AA          Total = 9 * 4 - (4 - nCorner)
			// Normal + Border      Total = 12 * 4 - (4 - nCorner) * 2
			// Normal               Total = 6 * 4

			//  Normal + AA + Border 
			//							TOTAL =  (8.5 * (m_nbSegments -1)) * nCorner + 14 * 4 - (4 - nCorner) * 2 + 4
			//  Normal + AA 
			//							TOTAL =  (4 * (m_nbSegments -1)) * nCorner + 9 * 4 - (4 - nCorner) + 4
			//  Normal + Border 
			//							TOTAL =  (6 * (m_nbSegments -1)) * nCorner + 12 * 4 - (4 - nCorner) * 2 + 4
			//  Normal 
			//							TOTAL =  (2.5 * (m_nbSegments -1)) * nCorner + 6 * 4 + 4
            const int nbVertice = (aa) ?
				(m_borderWidth > 0 ?
				(8.5f * (m_nbSegments - 2) + 8) * nCorner + (10 * 4) + 3 + (!m_topLeft ? 5 : 0) + (!m_topRight ? 4 : 0) + (!m_bottomRight ? 4 : 0) + (!m_bottomLeft ? 4 : 0) + nCorner :
					(4 * (m_nbSegments - 2) + 4) * nCorner + 6 * 4 + 3 + (!m_topLeft ? 4 : 0) + (!m_topRight ? 3 : 0) + (!m_bottomRight ? 3 : 0) + (!m_bottomLeft ? 3 : 0) + nCorner)
				:
				(m_borderWidth > 0 ?
				(6 * (m_nbSegments - 2) + 6) * nCorner + 8 * 4 + 3 + (!m_topLeft ? 3 : 0) + (!m_topRight ? 4 : 0) + (!m_bottomRight ? 4 : 0) + (!m_bottomLeft ? 4 : 0) + nCorner :
					(2.5f * (m_nbSegments - 2) + 2) * nCorner + 4 * 4 + 3 + (!m_topLeft ? 3 : 0) + (!m_topRight ? 2 : 0) + (!m_bottomRight ? 2 : 0) + (!m_bottomLeft ? 2 : 0) + nCorner)
                ;
            if (!oldNode) {
				node = new QSGGeometryNode;
				geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertice);
                geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
                const auto material = new QSGVertexColorMaterial;
                material->setFlag(QSGMaterial::Blending, true);
                node->setGeometry(geometry);
                node->setMaterial(material);
                node->setFlag(QSGNode::OwnsMaterial);
            }
            else {
                node = static_cast<QSGGeometryNode *>(oldNode);
                geometry = node->geometry();
                geometry->allocate(nbVertice);
            }

            auto vertices = geometry->vertexDataAsColoredPoint2D();
			const auto borderInner = m_radius + aaoffset;
			const auto borderOuter = borderInner + m_borderWidth;
			const auto outerAa = m_borderWidth > 0 ? borderOuter + aaoffset : borderInner;

			//    //Center
            vertices[++idx].set(w + center.x(), h + center.y(), r, g, b, alpha);
            vertices[++idx].set(-w + center.x(), h + center.y(), r, g, b, alpha);
            vertices[++idx].set(w + center.x(), -h + center.y(), r, g, b, alpha);

            const auto drawCircle = [&](qreal cx, qreal cy, float offset) {
				for (uint i = 0; i < m_nbSegments - 1; i++)
				{
					if (aa)
					{
						if (i % 2 == 0)
						{
                            vertices[++idx].set(cx, cy, r, g, b, alpha);

                            vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
                            vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
							if (m_borderWidth > 0)
							{
								vertices[++idx].set(cx + (borderInner)* qFastCos(a * i + offset), cy + borderInner * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + (borderInner)* qFastCos(a * (i + 1) + offset), cy + borderInner * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);

								vertices[++idx].set(cx + borderOuter * qFastCos(a * i + offset), cy + borderOuter * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + borderOuter * qFastCos(a * (i + 1) + offset), cy + borderOuter * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);

								vertices[++idx].set(cx + outerAa * qFastCos(a * i + offset), cy + outerAa * qFastSin(a * i + offset), ra, ga, ba, alphaa);
								vertices[++idx].set(cx + outerAa * qFastCos(a * (i + 1) + offset), cy + outerAa * qFastSin(a * (i + 1) + offset), ra, ga, ba, alphaa);
							}
							else
							{
								vertices[++idx].set(cx + outerAa * qFastCos(a * i + offset), cy + outerAa * qFastSin(a * i + offset), ra, ga, ba, alphaa);
								vertices[++idx].set(cx + outerAa * qFastCos(a * (i + 1) + offset), cy + outerAa * qFastSin(a * (i + 1) + offset), ra, ga, ba, alphaa);
							}
						}
						else
						{
							if (m_borderWidth > 0)
							{
								vertices[++idx].set(cx + outerAa * qFastCos(a * (i)+offset), cy + outerAa * qFastSin(a * (i)+offset), ra, ga, ba, alphaa);
								vertices[++idx].set(cx + outerAa * qFastCos(a * (i + 1) + offset), cy + outerAa * qFastSin(a * (i + 1) + offset), ra, ga, ba, alphaa);

								vertices[++idx].set(cx + borderOuter * qFastCos(a * i + offset), cy + borderOuter * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + borderOuter * qFastCos(a * (i + 1) + offset), cy + borderOuter * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);

								vertices[++idx].set(cx + borderInner * qFastCos(a * i + offset), cy + borderInner * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + borderInner * qFastCos(a * (i + 1) + offset), cy + borderInner * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);
							}
							else
							{
								vertices[++idx].set(cx + outerAa * qFastCos(a * (i + 1) + offset), cy + outerAa * qFastSin(a * (i + 1) + offset), ra, ga, ba, alphaa);
							}
							vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
							vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
						}
					}
					else
					{
						if (i % 2 == 0)
						{
							vertices[++idx].set(cx, cy, r, g, b, alpha);
							vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
							vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
							if (m_borderWidth > 0)
							{
								vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + borderOuter * qFastCos(a * i + offset), cy + borderOuter * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + borderOuter * qFastCos(a * (i + 1) + offset), cy + borderOuter * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);
							}
						}
						else
						{
							if (m_borderWidth > 0)
							{
								vertices[++idx].set(cx + borderOuter * qFastCos(a * (i + 1) + offset), cy + borderOuter * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), rb, gb, bb, alphab);
								vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), rb, gb, bb, alphab);
							}
							vertices[++idx].set(cx + m_radius * qFastCos(a * i + offset), cy + m_radius * qFastSin(a * i + offset), r, g, b, alpha);
							vertices[++idx].set(cx + m_radius * qFastCos(a * (i + 1) + offset), cy + m_radius * qFastSin(a * (i + 1) + offset), r, g, b, alpha);
						}
					}
				}
			};
			//Top
			if (m_topLeft)
				drawCircle(-w + center.x(), -h + center.y(), float(M_PI) / 2.0f * 2.0f);

			if (!m_topLeft)
			{
				vertices[++idx].set(-w + center.x(), -h + center.y(), r, g, b, alpha);
				vertices[++idx].set(-w + center.x(), -h + center.y(), r, g, b, alpha);
				vertices[++idx].set(-w + center.x() - m_radius, -h + center.y() - m_radius, r, g, b, alpha);
			}
			if (aa)
			{
				if (m_borderWidth > 0)
				{
					if (!m_topLeft)
					{
						vertices[++idx].set(-w + center.x() - borderInner, -h + center.y() - borderInner, rb, gb, bb, alphab);
						vertices[++idx].set(-w + center.x() - borderInner, -h + center.y() - borderInner, rb, gb, bb, alphab);
					}
					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : outerAa), -h + center.y() - outerAa, ra, ga, ba, alphaa);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : outerAa), -h + center.y() - outerAa, ra, ga, ba, alphaa);

					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : borderOuter), -h + center.y() - borderOuter, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : borderOuter), -h + center.y() - borderOuter, rb, gb, bb, alphab);

					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : borderInner), -h + center.y() - borderInner, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : borderInner), -h + center.y() - borderInner, rb, gb, bb, alphab);
				}
				else
				{
					if (!m_topLeft)
						vertices[++idx].set(-w + center.x() - borderOuter, -h + center.y() - borderOuter, rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : outerAa), -h + center.y() - outerAa, ra, ga, ba, alphaa);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : outerAa), -h + center.y() - outerAa, ra, ga, ba, alphaa);
				}
			}
			else
			{
				if (m_borderWidth > 0)
				{
					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : borderOuter), -h + center.y() - borderOuter, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : borderOuter), -h + center.y() - borderOuter, rb, gb, bb, alphab);

					vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : (m_radius)), -h + center.y() - (m_radius), rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_topRight ? 0 : (m_radius)), -h + center.y() - (m_radius), rb, gb, bb, alphab);
				}
			}
			vertices[++idx].set(-w + center.x() - (m_topLeft ? 0 : (m_radius)), -h + center.y() - (m_radius), r, g, b, alpha);
			vertices[++idx].set(w + center.x() + (m_topRight ? 0 : (m_radius)), -h + center.y() - (m_radius), r, g, b, alpha);
			vertices[++idx].set(-w + center.x(), -h + center.y(), r, g, b, alpha);
			vertices[++idx].set(w + center.x(), -h + center.y(), r, g, b, alpha);

            if (m_topRight)
                drawCircle(w + center.x(), -h + center.y(), float(M_PI) / 2.0f * 3.0f);
            if (!m_topRight)
            {
                vertices[++idx].set(w + center.x(), -h + center.y(), r, g, b, alpha);
                vertices[++idx].set(w + center.x() + m_radius, -h + center.y() - m_radius, r, g, b, alpha);
            }
			if (aa)
			{
				if (m_borderWidth > 0)
				{
					if (!m_topRight)
                    {
                        vertices[++idx].set(w + center.x() + borderInner, -h + center.y() - borderInner, rb, gb, bb, alphab);
                        vertices[++idx].set(w + center.x() + outerAa, -h + center.y() - (m_topRight ? 0 : outerAa), ra, ga, ba, alphaa);
                    }
                    vertices[++idx].set(w + center.x() + outerAa, -h + center.y() - (m_topRight ? 0 : outerAa), ra, ga, ba, alphaa);
                    vertices[++idx].set(w + center.x() + outerAa, h + center.y() + (m_bottomRight ? 0 : outerAa), ra, ga, ba, alphaa);
                    vertices[++idx].set(w + center.x() + borderOuter, -h + center.y() - (m_topRight ? 0 : borderOuter), rb, gb, bb, alphab);
                    vertices[++idx].set(w + center.x() + borderOuter, h + center.y() + (m_bottomRight ? 0 : borderOuter), rb, gb, bb, alphab);
                    vertices[++idx].set(w + center.x() + borderInner, -h + center.y() - (m_topRight ? 0 : borderInner), rb, gb, bb, alphab);
                    vertices[++idx].set(w + center.x() + borderInner, h + center.y() + (m_bottomRight ? 0 : borderInner), rb, gb, bb, alphab);
				}
				else
				{
					if (!m_topRight)
						vertices[++idx].set(w + center.x() + borderInner, -h + center.y() - borderInner, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + outerAa, -h + center.y() - (m_topRight ? 0 : outerAa), ra, ga, ba, alphaa);
					vertices[++idx].set(w + center.x() + outerAa, h + center.y() + (m_bottomRight ? 0 : outerAa), ra, ga, ba, alphaa);
				}
			}
			else if (m_borderWidth > 0)
			{
				if (!m_topRight)
				{
					vertices[++idx].set(w + center.x() + m_radius, -h + center.y() - m_radius, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + borderOuter, -h + center.y() - (m_topRight ? 0 : borderOuter), rb, gb, bb, alphab);
				}
				vertices[++idx].set(w + center.x() + borderOuter, -h + center.y() - (m_topRight ? 0 : borderOuter), rb, gb, bb, alphab);
				vertices[++idx].set(w + center.x() + borderOuter, h + center.y() + (m_bottomRight ? 0 : borderOuter), rb, gb, bb, alphab);
				vertices[++idx].set(w + center.x() + m_radius, -h + center.y() - (m_topRight ? 0 : (m_radius)), rb, gb, bb, alphab);
				vertices[++idx].set(w + center.x() + m_radius, h + center.y() + (m_bottomRight ? 0 : (m_radius)), rb, gb, bb, alphab);
            }
            vertices[++idx].set(w + center.x() + m_radius, -h + center.y() - (m_topRight ? 0 : (m_radius)), r, g, b, alpha);
            vertices[++idx].set(w + center.x() + m_radius, h + center.y() + (m_bottomRight ? 0 : (m_radius)), r, g, b, alpha);
            vertices[++idx].set(w + center.x(), -h + center.y(), r, g, b, alpha);
            vertices[++idx].set(w + center.x(), h + center.y(), r, g, b, alpha);

			if (m_bottomRight)
				drawCircle(w + center.x(), h + center.y(), 0);
			if (!m_bottomRight)
			{
				vertices[++idx].set(w + center.x(), h + center.y(), r, g, b, alpha);
				vertices[++idx].set(w + center.x() + m_radius, h + center.y() + m_radius, r, g, b, alpha);
			}
			if (aa)
			{
				if (m_borderWidth > 0)
				{
					if (!m_bottomRight)
					{
						vertices[++idx].set(w + center.x() + borderInner, h + center.y() + borderInner, rb, gb, bb, alphab);
						vertices[++idx].set(w + center.x() + borderOuter, h + center.y() + borderOuter, rb, gb, bb, alphab);
					}
					vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : outerAa), h + center.y() + outerAa, ra, ga, ba, alphaa);
					vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : outerAa), h + center.y() + outerAa, ra, ga, ba, alphaa);

					vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : borderOuter), h + center.y() + borderOuter, rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : borderOuter), h + center.y() + borderOuter, rb, gb, bb, alphab);

					vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : borderInner), h + center.y() + borderInner, rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : borderInner), h + center.y() + borderInner, rb, gb, bb, alphab);
				}
				else
				{
					if (!m_bottomRight)
						vertices[++idx].set(w + center.x() + borderInner, h + center.y() + borderInner, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : outerAa), h + center.y() + outerAa, ra, ga, ba, alphaa);
					vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : outerAa), h + center.y() + outerAa, ra, ga, ba, alphaa);
				}
			}
			else if (m_borderWidth > 0)
			{
				if (!m_bottomRight)
				{
					vertices[++idx].set(w + center.x() + m_radius, h + center.y() + m_radius, rb, gb, bb, alphab);
					vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : borderOuter), h + center.y() + borderOuter, rb, gb, bb, alphab);
				}
				vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : borderOuter), h + center.y() + borderOuter, rb, gb, bb, alphab);
				vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : borderOuter), h + center.y() + borderOuter, rb, gb, bb, alphab);
				vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : (m_radius)), h + center.y() + (m_radius), rb, gb, bb, alphab);
				vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : (m_radius)), h + center.y() + (m_radius), rb, gb, bb, alphab);
			}
			vertices[++idx].set(w + center.x() + (m_bottomRight ? 0 : (m_radius)), h + center.y() + (m_radius), r, g, b, alpha);
			vertices[++idx].set(-w + center.x() - (m_bottomLeft ? 0 : (m_radius)), h + center.y() + (m_radius), r, g, b, alpha);
			vertices[++idx].set(w + center.x(), h + center.y(), r, g, b, alpha);
			vertices[++idx].set(-w + center.x(), h + center.y(), r, g, b, alpha);

			if (m_bottomLeft)
				drawCircle(-w + center.x(), h + center.y(), float(M_PI) / 2.0f);
			if (!m_bottomLeft)
			{
				vertices[++idx].set(-w + center.x(), h + center.y(), r, g, b, alpha);
				vertices[++idx].set(-w + center.x() - m_radius, h + center.y() + m_radius, r, g, b, alpha);
			}
			if (aa)
			{
				if (m_borderWidth > 0)
				{
					if (!m_bottomLeft)
					{
						vertices[++idx].set(-w + center.x() - borderInner, h + center.y() + borderInner, rb, gb, bb, alphab);
						vertices[++idx].set(-w + center.x() - borderOuter, h + center.y() + borderOuter, rb, gb, bb, alphab);
					}
					vertices[++idx].set(-w + center.x() - outerAa, h + center.y() + (m_bottomLeft ? 0 : outerAa), ra, ga, ba, alphaa);
					vertices[++idx].set(-w + center.x() - outerAa, -h + center.y() - (m_topLeft ? 0 : outerAa), ra, ga, ba, alphaa);

					vertices[++idx].set(-w + center.x() - borderOuter, h + center.y() + (m_bottomLeft ? 0 : borderOuter), rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - borderOuter, -h + center.y() - (m_topLeft ? 0 : borderOuter), rb, gb, bb, alphab);

					vertices[++idx].set(-w + center.x() - borderInner, h + center.y() + (m_bottomLeft ? 0 : borderInner), rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - borderInner, -h + center.y() - (m_topLeft ? 0 : borderInner), rb, gb, bb, alphab);
				}
				else
				{
					if (!m_bottomLeft)
						vertices[++idx].set(-w + center.x() - borderInner, h + center.y() + borderInner, rb, gb, bb, alphab);
					vertices[++idx].set(-w + center.x() - outerAa, h + center.y() + (m_bottomLeft ? 0 : outerAa), ra, ga, ba, alphaa);
					vertices[++idx].set(-w + center.x() - outerAa, -h + center.y() - (m_topLeft ? 0 : outerAa), ra, ga, ba, alphaa);
				}
			}
			else if (m_borderWidth > 0)
			{
				if (!m_bottomLeft)
				{
					vertices[++idx].set(-w + center.x() - m_radius, h + center.y() + m_radius, rb, gb, bb, alpha);
					vertices[++idx].set(-w + center.x() - borderOuter, h + center.y() + (m_bottomLeft ? 0 : borderOuter), rb, gb, bb, alphab);
				}
				vertices[++idx].set(-w + center.x() - borderOuter, h + center.y() + (m_bottomLeft ? 0 : borderOuter), rb, gb, bb, alphab);
				vertices[++idx].set(-w + center.x() - borderOuter, -h + center.y() - (m_topLeft ? 0 : borderOuter), rb, gb, bb, alphab);
				vertices[++idx].set(-w + center.x() - m_radius, h + center.y() + (m_bottomLeft ? 0 : (m_radius)), rb, gb, bb, alphab);
				vertices[++idx].set(-w + center.x() - m_radius, -h + center.y() - (m_topLeft ? 0 : (m_radius)), rb, gb, bb, alphab);
			}
			vertices[++idx].set(-w + center.x() - m_radius, h + center.y() + (m_bottomLeft ? 0 : (m_radius)), r, g, b, alpha);
			vertices[++idx].set(-w + center.x() - m_radius, -h + center.y() - (m_topLeft ? 0 : (m_radius)), r, g, b, alpha);
			vertices[++idx].set(-w + center.x(), h + center.y(), r, g, b, alpha);
			vertices[++idx].set(-w + center.x(), -h + center.y(), r, g, b, alpha);

            Q_ASSERT(idx + 1 == nbVertice);
            node->markDirty(QSGNode::DirtyGeometry);
			return  node;
		}
	}
}
