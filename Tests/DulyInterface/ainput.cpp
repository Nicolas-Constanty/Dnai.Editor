#include <QDebug>
#include <QBrush>
#include <QPainter>
#include "anode.h"
#include "ainput.h"
#include "nodemanager.h"
#include "linewidget.h"

AInput::AInput(int x, int y, int width, int height, QGraphicsItem *parent, ANode *node)
    : QGraphicsRectItem(x, y, width, height, parent),
      m_node(node),
      m_origin(false)
{
    line = NULL;
    isP1 = false;
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    //setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void AInput::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    qDebug() << "PRESS"<< this;
    m_origin = true;
   //LineWidget *line = new LineWidget();
  // line->setParent(m_node->parentWidget());
  // line->show();

    //NodeManager::Shared().setSelectedNode(m_node);
    //NodeManager::Shared().setSelectedInput(this);

}

void AInput::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    qDebug() << "RELEASE" << this;
}

void AInput::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    /*if (NodeManager::Shared().selectedInput()
            && NodeManager::Shared().selectedInput() != this) {
        qDebug() << NodeManager::Shared().selectedInput() << " TO " << this;
        NodeManager::Shared().setSelectedNode(NULL);
        NodeManager::Shared().setSelectedInput(NULL);
    }*/
    /*if (NodeManager::Shared().selectedNode()) {

    }*/
    qDebug() << "ENTER"<< this;
    setBrush(QBrush(QColor(Qt::green)));
}

void AInput::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    qDebug() << "LEAVE"<< this;
    setBrush(QBrush(QColor(Qt::yellow)));
}
