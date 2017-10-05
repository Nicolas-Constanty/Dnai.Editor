#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>

#include "dulycanvas.h"
#include "genericnode.h"

GenericNode::GenericNode(QQuickItem *parent) :
    QQuickItem(parent)
{
    DulyCanvas::Instance->focusManager().registerItem(this);
    setFlag(ItemHasContents, true);
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
