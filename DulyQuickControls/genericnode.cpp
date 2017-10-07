#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>


#include "input.h"
#include "output.h"
#include "dulycanvas.h"
#include "genericnode.h"

GenericNode::GenericNode(QQuickItem *parent) :
    QQuickItem(parent)
{
    DulyCanvas::Instance->focusManager().registerItem(this);
    setFlag(ItemHasContents, true);
	setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::LeftButton);
	setFlag(ItemAcceptsInputMethod, true);
}

void GenericNode::setFlowIn(bool f)
{

    if (f == m_flowIn)
		return;
    m_flowIn = f;
    emit flowInChanged(f);
}

void GenericNode::setFlowOut(bool f)
{
    if (f == m_flowOut)
		return;
	m_flowOut = f;
    emit flowOutChanged(f);
}

void GenericNode::setFlowInItem(Flow *f)
{
    if (f == m_flowInItem || nullptr)
        return;
    m_flowInItem = f;
}

void GenericNode::setFlowOutItem(Flow *f)
{
    if (f == m_flowOutItem || nullptr)
        return;
    m_flowOutItem = f;
}

void GenericNode::setHeader(RoundedRectangle *h)
{
    if (h == m_header)
        return;
    m_header = h;
    m_header->setParent(this);
    emit headerChanged(h);
}

void GenericNode::setContent(RoundedRectangle *c)
{
    if (c == m_content)
        return;
    m_content = c;
    m_content->setParent(this);
    emit contentChanged(c);
}

void GenericNode::mouseMoveEvent(QMouseEvent* event)
{
    QPointF p(mapToItem(DulyCanvas::Instance, event->pos()) + m_offset);
    setX(p.x());
    setY(p.y());
    updateInputs();
    updateOutputs();
    if (m_flowInItem && m_flowInItem->isVisible())
        m_flowInItem->updateLink();
    if (m_flowOutItem && m_flowOutItem->isVisible())
        m_flowOutItem->updateLink();
}

void GenericNode::updateInputs()
{
    auto list = m_inputs.getList();
    for (int i = 0; i < list.size(); i++)
    {
        auto input = dynamic_cast<Input *>(list.at(i));
        if (input && input->getLinkable()->isLink())
        {
            input->updateLink();
        }
    }
}

void GenericNode::updateOutputs()
{
    auto list = m_outputs.getList();
    for (int i = 0; i < list.size(); i++)
    {
        auto output = dynamic_cast<Output *>(list.at(i));
        if (output && output->getLinkable()->isLink())
        {
            output->updateLink();
        }
    }
}

void GenericNode::mousePressEvent(QMouseEvent* event)
{
    m_offset = QPointF(position() - mapToItem(DulyCanvas::Instance, event->pos()));
}

void GenericNode::mouseReleaseEvent(QMouseEvent *)
{
    m_offset.setX(0);
    m_offset.setY(0);
}

QSGNode *GenericNode::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
	auto n = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!n) {
       n = new QSGSimpleRectNode();
    }
    n->setColor(Qt::transparent);
    n->setRect(boundingRect());

    return n;
}

void GenericNode::componentComplete()
{
    QQuickItem::componentComplete();

}
