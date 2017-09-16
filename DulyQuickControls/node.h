#ifndef NODE_H
#define NODE_H

#include <QObject>
#include "border.h"

class Node : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(Border border READ border WRITE setBorder NOTIFY borderChanged)
public:
    explicit Node(QObject *parent = nullptr);

//    const Border &border() const;
//    void setBorder(const Border &b);

//signals:
//    void borderChanged();

//private:
//    Border m_border;

public slots:
};

#endif // NODE_H
