#include <QSGVertexColorMaterial>
#include <QtMath>

#include "dnai/link.h"
#include "dnai/views/genericnode.h"
#include "dnai/views/flow.h"

namespace dnai
{
	namespace views
	{
		FlowBackend::FlowBackend(enums::FlowTypeRessouce::FlowType t, QQuickItem* parent) :
			BaseLinkable(parent),
			m_typeFlow(t)
		{
		}

        enums::FlowTypeRessouce::FlowType FlowBackend::getType() const
		{
            return m_typeFlow;
		}

		Link* FlowBackend::connect(ALinkable* linkable, BezierCurve* curve)
		{
			const auto li = dynamic_cast<FlowBackend *>(linkable);
			if (li != nullptr && li->getType() != getType())
			{
				const auto f = dynamic_cast<Flow *>(li->parent());
				if (!li->links().empty() && f->typeFlow() == enums::FlowTypeRessouce::FlowType::Exit)
				{
					f->unlinkAll();
				}
				const auto l = BaseLinkable::connect(linkable, curve);
				if (const auto fl = dynamic_cast<Flow *>(parent()))
				{
					const auto flow = dynamic_cast<dnai::views::Flow *>(li->parent());
					int index;
					if (flow->typeFlow() == enums::FlowTypeRessouce::FlowType::Exit)
					{
						
						index = flow->getNode()->flowsOut().getList().indexOf(flow);
					}
					else
					{
						const auto flowp = dynamic_cast<dnai::views::Flow *>(parent());
						index = flowp->getNode()->flowsOut().getList().indexOf(flowp);
					}
					emit fl->linked(index, flow->getNode()->property("instruction_model"));
				}
				return l;
			}
			return nullptr;
		}

		Flow::Flow(QQuickItem* parent) :
			LinkableBezierItem(parent)
            , m_typeFlow(enums::FlowTypeRessouce::FlowType::Enter)
			, m_genericNode(nullptr)
		{
			setFlag(ItemHasContents, true);
			m_radius = 8;
			m_borderWidth = 2;
			CustomShape::setFillColor(QColor(96, 96, 96));
			CustomShape::setBorderColor(QColor(255, 255, 255));
		}

		QSGNode* Flow::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData *data)
		{
			CustomShape::updatePaintNode(oldNode, data);
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
            const char r = m_fillColor.red() * m_fillColor.alphaF();
            const char g = m_fillColor.green() * m_fillColor.alphaF();
            const char b = m_fillColor.blue() * m_fillColor.alphaF();
            const char alpha = m_fillColor.alpha();

            const char rb = m_borderColor.red() * m_borderColor.alphaF();
            const char gb = m_borderColor.green() * m_borderColor.alphaF();
            const char bb = m_borderColor.blue() * m_borderColor.alphaF();
            const char alphab = m_borderColor.alpha();

			const auto aa = antialiasing();
			setWidth((m_radius + m_radius / 2.5f) * 2);
			setHeight((m_radius + m_radius / 2.5f) * 2);
			const auto nbQuarter = 3;
			const uint nbVertices = 1 + (aa ? (m_borderWidth > 0 ? 16 * nbQuarter : 9 * nbQuarter) : (m_borderWidth > 0 ? 13 * nbQuarter : 5 * nbQuarter));
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
			const auto aMax = qDegreesToRadians(360.f / nbQuarter);
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
			node->markDirty(QSGNode::DirtyGeometry);
			return node;
		}

        void Flow::setTypeFlow(enums::FlowTypeRessouce::FlowType t)
		{
            if (t == m_typeFlow && m_linkable != nullptr)
				return;
            m_typeFlow = t;
			delete m_linkable;
			m_linkable = new FlowBackend(t, this);
            emit typeFlowChanged(t);
			update();
		}

		void Flow::componentComplete()
		{
			QQuickItem::componentComplete();
            GenericNode *n = nullptr;
			auto parent = parentItem();
            while (n == nullptr && parent != nullptr)
            {
                n = dynamic_cast<GenericNode *>(parent);
                if (n)
                {
					if (m_typeFlow == enums::FlowTypeRessouce::FlowType::Exit)
					{
						n->flowsOut().registerItem(this);
					}
					else {
						n->flowsIn().registerItem(this);
					}
					break;
                }
                parent = parent->parentItem();
            }
		}

        QPointF Flow::getCanvasPos() const
        {
            return QPointF(mapToItem(m_canvas->content(), QPoint(0,0)) +
                           QPointF(width() / 2, height() / 2));
        }

		void Flow::unlinkAll()
		{
			for (auto link : m_linkable->links())
			{
				int index;
				QVariant instruction;
				const auto flow1 = dynamic_cast<Flow*>(dynamic_cast<FlowBackend*>(link->L1)->parent());
				const auto flow2 = dynamic_cast<Flow*>(dynamic_cast<FlowBackend*>(link->L2)->parent());
				if (flow1->typeFlow() == enums::FlowTypeRessouce::FlowType::Exit)
				{
					index = flow1->getNode()->flowsOut().getList().indexOf(flow1);
					instruction = flow1->getNode()->property("instruction_model");
				}
				else
				{
					index = flow2->getNode()->flowsOut().getList().indexOf(flow2);
					instruction = flow2->getNode()->property("instruction_model");
				}
				emit unlinked(index, instruction);
			}

			LinkableBezierItem::unlinkAll(); 
		}

		const QColor& Flow::colorLink() const
		{
			return m_borderColor;
		}

		LinkableBezierItem* Flow::findLinkableBezierItem(GenericNode* n, const QPointF&p)
		{
            if (m_typeFlow == enums::FlowTypeRessouce::FlowType::Exit)
            {
                auto qlist = n->flowsIn().findFocused(p);
                return (!qlist.empty()) ? dynamic_cast<Flow*>(qlist.at(0)) : nullptr;
            }
            else if (m_typeFlow == enums::FlowTypeRessouce::FlowType::Enter)
            {
                auto qlist = n->flowsOut().findFocused(p);
                return (!qlist.empty()) ? dynamic_cast<Flow*>(qlist.at(0)) : nullptr;
            }
			return nullptr;
		}

		void Flow::updateLink()
		{
			auto list = m_linkable->links();
			for (auto l : list)
			{
				l->curve()->setPosition(getCanvasPos());
				const auto io = dynamic_cast<Flow *>(dynamic_cast<FlowBackend *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
				l->curve()->setP4(io->getCanvasPos());
			}
		}

        GenericNode* Flow::getNode()
		{
			if (m_genericNode == nullptr)
			{
				GenericNode *n = nullptr;
				QQuickItem *parent = parentItem();
				while (n == nullptr && parent != nullptr)
				{
					n = dynamic_cast<GenericNode *>(parent);
					if (n)
					{
						m_genericNode = n;
						break;
					}
					parent = parent->parentItem();
				}
			}
			return m_genericNode;
		}

		void Flow::setLink(Link *l)
		{
			setBorderWidth(0);
			setFillColor(QColor(255, 255, 255));
			if (l == nullptr) return;
			auto f = dynamic_cast<Flow *>(dynamic_cast<FlowBackend *>(l->L1 != m_linkable ? l->L1 : l->L2)->parent());
			f->setLink(nullptr);
			LinkableBezierItem::setLink(nullptr);
		}

		void Flow::setHover()
		{
			if (m_status == LinkStatus::Hover) return;
			setBorderColor(QColor(255, 170, 0));
			setFillColor(QColor(255, 170, 0));
			LinkableBezierItem::setHover();
		}


		void Flow::afterRealease(Link *l)
		{
			if (l == nullptr)
			{
				unlinkAll();
			}
		}

		void Flow::mousePressEvent(QMouseEvent* event)
		{
			LinkableBezierItem::mousePressEvent(event);
			if (m_currentCurve)
				m_currentCurve->setLineWidth(3);
		}
	}
}

