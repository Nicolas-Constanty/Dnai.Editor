#ifndef DECLARATIONTYPE_H
#define DECLARATIONTYPE_H

#include <QObject>

namespace dnai {
namespace qmlresources {
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
}
}


#endif // DECLARATIONTYPE_H
