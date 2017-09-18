#include "nodemanager.h"

NodeManager::NodeManager()
    : QObject(),
      m_nodes(),
      m_selectedNode(NULL),
      m_selectedInput(NULL)
{

}

NodeManager &NodeManager::Shared() {
    static NodeManager nodeManager;

    return (nodeManager);
}

void NodeManager::setSelectedNode(ANode *node) {
    m_selectedNode = node;
}

ANode *NodeManager::addNode(QGraphicsScene *scene) {
    ANode *anode = new ANode(10, 4);
    scene->addItem(anode);

    m_nodes.push_back(anode);
    return (anode);
}

ANode *NodeManager::selectedNode() const {
    return (m_selectedNode);
}

void NodeManager::setSelectedInput(AInput *input) {
    m_selectedInput = input;
}

AInput *NodeManager::selectedInput() const {
    return (m_selectedInput);
}
