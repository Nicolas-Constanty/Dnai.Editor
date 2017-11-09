#ifndef RESOURCESNODE_H
#define RESOURCESNODE_H

#include <QObject>

class DulyResources : public QObject
{
    Q_OBJECT
public:
    explicit DulyResources(QObject *parent = nullptr) : QObject(parent) {}
    ~DulyResources() {}
    /**
    * \brief define all the handle type by the application
    */
    enum IoType
    {
        Int,
        Float,
        Double,
        String,
        Bool,
        Object,
        Generic,
        Count //Get the size of enum, must be at the end all the time!
    };
    Q_ENUM(IoType)

        enum FlowType
    {
        Enter,
        Exit
    };
    Q_ENUM(FlowType)
};

#endif // RESOURCESNODE_H
