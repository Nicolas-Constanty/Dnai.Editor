#include <QSGVertexColorMaterial>

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
}

QSGNode* Flow::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
	QSGGeometryNode *node;
	QSGGeometry *geometry;

	const uint nbVertices = 1000;
	if (!oldNode) {
		node = new QSGGeometryNode;
		geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), nbVertices);
		geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
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
