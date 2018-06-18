#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QGraphicsScene>
#include <QList>
#include "anode.h"
#include "ainput.h"

class NodeManager : public QObject
{
    Q_OBJECT

public:
    NodeManager();

    static NodeManager &Shared();

    ANode * addNode(QGraphicsScene *);
    void setSelectedNode(ANode *);
    ANode *selectedNode() const;

    void setSelectedInput(AInput *);
    AInput *selectedInput() const;

private:
    QList<ANode *>  m_nodes;
    ANode           *m_selectedNode;
    AInput          *m_selectedInput;
};

#endif // NODEMANAGER_H
