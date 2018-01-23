#ifndef LAYOUTHANDLER_H
#define LAYOUTHANDLER_H

#include <QObject>

class LayoutHandler : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QObjectList views READ views WRITE setViews NOTIFY viewsChanged)

public:
    explicit LayoutHandler(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LAYOUTHANDLER_H
