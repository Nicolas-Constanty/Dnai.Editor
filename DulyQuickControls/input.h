#ifndef INPUT_H
#define INPUT_H

#include <QtQuick/QQuickItem>

#include "baseio.h"
#include "io.h"

class InputBackend : public BaseIO
{
public:
    InputBackend(DulyResources::IOType t) : BaseIO() {
        m_type = t;
    }

    const std::shared_ptr<Link> &Connect(ALinkable *linkable) override;
private:
    InputBackend() {}
};

class Input : public IO
{
public:
    Input (QQuickItem *parent = 0);

    void refreshBackendIO() override;
};
#endif // INPUT_H
