#include <QSGVertexColorMaterial>
#include <QtMath>

#include "flow.h"
#include "resourcesnode.h"
#include "dulycanvas.h"
#include "link.h"
#include "genericnode.h"

FlowBackend::FlowBackend(DulyResources::FlowType t, QQuickItem* parent) : 
	BaseLinkable(parent),
	m_type(t)
{
}

DulyResources::FlowType FlowBackend::getType() const
{
	return m_type;
}

Link* FlowBackend::connect(ALinkable* linkable, BezierCurve* curve)
{
    const auto li = dynamic_cast<FlowBackend *>(linkable);
	if (li != nullptr && li->getType() != getType())
    {
		return BaseLinkable::connect(linkable, curve);
	}
	return nullptr;
}

Flow::Flow(QQuickItem* parent):
    LinkableBezierItem(parent)
    , m_type(DulyResources::FlowType::Enter)
{
    setFlag(ItemHasContents, true);
    m_radius = 8;
    m_borderWidth = 2;
    m_fillColor = QColor(96, 96, 96);
    m_borderColor = QColor(255, 255, 255);
}

QSGNode* Flow::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
    QSGGeometryNode *node;
    QSGGeometry *geometry;
    if (!isVisible())
    {
        if (oldNode)
        {
            node = static_cast<QSGGeometryNode *>(oldNode);
            geometry = node->geometry();
            geometry->allocate(0);
        }
        return nullptr;
    }
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
    const auto aMin = qDegreesToRadians(10.f); // 5 deg
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
            vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMax + aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMax + aMin), rb, gb, bb, alphab);
            vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMin), rb, gb, bb, alphab);

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

            vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a - aMin), cy + (m_radius + aaoffset) * qFastSin(a - aMin), rb, gb, bb, alphab);
            vertices[++idx].set(cx + (m_radius + aaoffset) * qFastCos(a + aMin), cy + (m_radius + aaoffset) * qFastSin(a + aMin), rb, gb, bb, alphab);
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
    if (t == m_type && m_linkable != nullptr)
		return;
	m_type = t;
    if (m_linkable)
        delete m_linkable;
    m_linkable = new FlowBackend(t, this);
	emit typeChanged(t);
	update();
}

void Flow::componentComplete()
{
	QQuickItem::componentComplete();
}

QPointF Flow::getCanvasPos() const
{
    return QPointF(parentItem()->position() + position() + QPointF(width() / 2, height() / 2));
}

const QColor& Flow::colorLink() const
{
	return m_borderColor;
}

LinkableBezierItem* Flow::findLinkableBezierItem(GenericNode* n, const QPointF&)
{
	if (m_type == DulyResources::FlowType::Exit)
		return n->flowInItem();
	else
		return n->flowOutItem();
}

void Flow::updateLink()
{
	auto list = m_linkable->links();
	for (auto i = 0; i < list.size(); i++)
	{
		const auto l = list.at(i);
        l->curve()->setPosition(mapToItem(DulyCanvas::Instance, QPointF(width() / 2, height() / 2)));
		const auto io = dynamic_cast<Flow *>(dynamic_cast<FlowBackend *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
		l->curve()->setP4(io->getCanvasPos());
	}
}

GenericNode* Flow::getNode() const
{
	return dynamic_cast<GenericNode *>(parentItem());
}

void Flow::mousePressEvent(QMouseEvent* event)
{
	LinkableBezierItem::mousePressEvent(event);
	if (m_currentCurve)
        m_currentCurve->setLineWidth(3);
}

void Flow::mouseReleaseEvent(QMouseEvent* event)
{
    LinkableBezierItem::mouseReleaseEvent(event);
    if (m_linkable->isLink())
    {
        setBorderWidth(0);
        setFillColor(m_borderColor);
        auto list = m_linkable->links();
        for (auto i = 0; i < list.size(); i++)
        {
            const auto l = list.at(i);
            auto f = dynamic_cast<Flow *>(dynamic_cast<FlowBackend *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
            f->setBorderWidth(0);
            f->setFillColor(m_borderColor);
        }

    }
}
