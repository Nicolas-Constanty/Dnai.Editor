#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>


#include "genericnode.h"

GenericNode::GenericNode(QQuickItem *parent) : QQuickItem(parent)
{

}

void GenericNode::setBackgroundColor(const QColor &color)
{
    if (color == m_backgroundColor)
        return;
    m_backgroundColor = color;
    emit backgroundColorChanged(color);
    update();
}


QSGNode *GenericNode::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!n) {
       n = new QSGSimpleRectNode();
    }
    n->setColor(m_backgroundColor);
    n->setRect(boundingRect());
    return n;
}
