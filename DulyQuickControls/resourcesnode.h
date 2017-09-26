#ifndef RESOURCESNODE_H
#define RESOURCESNODE_H

#include <QObject>

class DulyResources  : public QObject
{
   Q_OBJECT
   public:
    DulyResources(QObject *parent = 0) : QObject(parent) {}
    ~DulyResources() {}
    enum IOType
    {
        Int,
        String,
        Bool,
        Count
    };
    Q_ENUM(IOType)
};



#endif // RESOURCESNODE_H
