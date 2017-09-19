#ifndef DULYSCENE_H
#define DULYSCENE_H

#include <QObject>
#include <QQuickItem>

class DulyScene : public QQuickItem
{
    Q_OBJECT

public:
    DulyScene(QObject *parent = 0);

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

private:
    //int m_scene;
    //QGraphicsScene *m_scene;
};

#endif // DULYSCENE_H
