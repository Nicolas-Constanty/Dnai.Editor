#include <QSGVertexColorMaterial>
#include <QtMath>

#include "flow.h"
#include "resourcesnode.h"



FlowBackend::FlowBackend(DulyResources::FlowType t, QQuickItem* parent) : BaseLinkable(parent), m_type(t)
{
}

DulyResources::FlowType FlowBackend::getType() const
{
	return m_type;
}

Flow::Flow(QQuickItem* parent):
    CustomShape(parent)
    , m_type(DulyResources::FlowType::Enter)
	, m_flow(nullptr)
{
	setFlag(ItemHasContents, true);
	setAntialiasing(true);
}

QSGNode* Flow::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
	QSGGeometryNode *node;
	QSGGeometry *geometry;
	const char r = m_fillColor.red();
	const char g = m_fillColor.green();
	const char b = m_fillColor.blue();
	const char alpha = m_fillColor.alpha();

	const char rb = m_borderColor.red();
	const char gb = m_borderColor.green();
	const char bb = m_borderColor.blue();
	const char alphab = m_borderColor.alpha();

	const auto aa = antialiasing();
	setWidth((m_radius + m_radius / 2.5f) * 2);
	setHeight((m_radius + m_radius / 2.5f) * 2);
	const auto nbQuarter = 3;
	const uint nbVertices = 1 + (aa?(m_borderWidth > 0 ? 16 * nbQuarter: 9 * nbQuarter):(m_borderWidth > 0 ? 13 * nbQuarter : 5 * nbQuarter));
	if (!oldNode) {
		node = new QSGGeometryNode;
		geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertices);
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

	const auto vertices = geometry->vertexDataAsColoredPoint2D();
	auto idx = -1;
	const auto cx = width() / 2;
	const auto cy = height() / 2;
	const auto aMin = qDegreesToRadians(5.f); // 5 deg
	const auto aMax = qDegreesToRadians(360.f/nbQuarter);
	const qreal aaoffset = 1;
	auto a = 0.f;
	const auto drawQuarter = [&]()
	{
		vertices[++idx].set(cx, cy, r, g, b, alpha);
		vertices[++idx].set(cx + m_radius * qFastCos(a + aMin), cy + m_radius * qFastSin(a + aMin), r, g, b, alpha);
		a += aMax;
		vertices[++idx].set(cx + m_radius * qFastCos(a - aMin), cy + m_radius * qFastSin(a - aMin), r, g, b, alpha);
		if (m_borderWidth > 0)
		{
			vertices[++idx].set(cx + (m_radius - aaoffset) * qFastCos(a - aMax + aMin), cy + (m_radius - aaoffset) * qFastSin(a - aMax + aMin), rb, gb, bb, alphab);
			vertices[++idx].set(cx + (m_radius - aaoffset) * qFastCos(a - aMin), cy + (m_radius - aaoffset) * qFastSin(a - aMin), rb, gb, bb, alphab);

			vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a - aMax + aMin), cy + (m_radius + m_borderWidth) * qFastSin(a - aMax + aMin), rb, gb, bb, alphab);
			vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a - aMin), cy + (m_radius + m_borderWidth) * qFastSin(a - aMin), rb, gb, bb, alphab);

			if (aa)
			{
				vertices[++idx].set(cx + (m_radius + m_borderWidth + aaoffset) * qFastCos(a - aMax + aMin), cy + (m_radius + m_borderWidth + aaoffset) * qFastSin(a - aMax + aMin), 0, 0, 0, 0);
				vertices[++idx].set(cx + (m_radius + m_borderWidth + aaoffset) * qFastCos(a - aMin), cy + (m_radius + m_borderWidth + aaoffset) * qFastSin(a - aMin), 0, 0, 0, 0);

				vertices[++idx].set(cx + (m_radius + m_borderWidth + aaoffset) * qFastCos(a + aMin), cy + (m_radius + m_borderWidth + aaoffset) * qFastSin(a + aMin), 0, 0, 0, 0);
			}
			vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a - aMin), cy + (m_radius + m_borderWidth) * qFastSin(a - aMin), rb, gb, bb, alphab);
			vertices[++idx].set(cx + (m_radius + m_borderWidth) * qFastCos(a + aMin), cy + (m_radius + m_borderWidth) * qFastSin(a + aMin), rb, gb, bb, alphab);

			vertices[++idx].set(cx + (m_radius - aaoffset) * qFastCos(a - aMin), cy + (m_radius - aaoffset) * qFastSin(a - aMin), rb, gb, bb, alphab);
			vertices[++idx].set(cx + (m_radius - aaoffset) * qFastCos(a + aMin), cy + (m_radius - aaoffset) * qFastSin(a + aMin), rb, gb, bb, alphab);
		}
		else if (aa)
		{
			vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMax + aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMax + aMin), 0, 0, 0, 0);
			vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMin), 0, 0, 0, 0);

			vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMin), 0, 0, 0, 0);
			vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a + aMin), cy + (m_radius + aaoffset) * qFastSin(a + aMin), 0, 0, 0, 0);
		}
		vertices[++idx].set(cx + m_radius * qFastCos(a - aMin), cy + m_radius * qFastSin(a - aMin), r, g, b, alpha);
		vertices[++idx].set(cx + m_radius * qFastCos(a + aMin), cy + m_radius * qFastSin(a + aMin), r, g, b, alpha);
	};
	for (auto i = 0; i < nbQuarter; i++)
		drawQuarter();
	vertices[++idx].set(cx, cy, r, g, b, alpha);

	return node;
}

void Flow::setType(DulyResources::FlowType t)
{
	if (t == m_type)
		return;
	m_type = t;
	if (m_flow)
		delete m_flow;
	m_flow = new FlowBackend(t, this);
	emit typeChanged(t);
	update();
}
