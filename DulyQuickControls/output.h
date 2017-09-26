#ifndef OUTPUT_H
#define OUTPUT_H

#include "baseio.h"
#include "io.h"

class OutputBackend : public BaseIO
{
public:
    OutputBackend(DulyResources::IOType type) : BaseIO() {
        m_type = type;
    }

    const std::shared_ptr<Link> &Connect(ALinkable *linkable) override;
private:
    OutputBackend() {}
};

class Output : public IO
{

public:
    Output (QQuickItem *parent = 0);

    void refreshBackendIO() override;

private:

};
#endif // OUTPUT_H
