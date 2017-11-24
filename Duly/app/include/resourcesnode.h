#ifndef RESOURCESNODE_H
#define RESOURCESNODE_H

#include <QObject>

class IoTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit IoTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~IoTypeRessouce() {}
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
};

class DeclarationTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit DeclarationTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~DeclarationTypeRessouce() {}

    enum DeclarationType
    {
        None,
        Context,
        Class,
        Variable,
        Function
    };
    Q_ENUM(DeclarationType)
};

class FlowTypeRessouce : public QObject
{
    Q_OBJECT
public:
    explicit FlowTypeRessouce(QObject *parent = nullptr) : QObject(parent) {}
    ~FlowTypeRessouce() {}

    enum FlowType
    {
        Enter,
        Exit
    };
    Q_ENUM(FlowType)
};

typedef IoTypeRessouce::IoType IoType;
typedef FlowTypeRessouce::FlowType FlowType;
typedef DeclarationTypeRessouce::DeclarationType DeclarationType;

#endif // RESOURCESNODE_H
