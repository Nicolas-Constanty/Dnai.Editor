#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "output.h"
#include "input.h"

const std::shared_ptr<Link> &OutputBackend::Connect(ALinkable *linkable)
{
	const auto li = dynamic_cast<InputBackend *>(linkable);
    if (li != nullptr && li->GetType() == GetType())
    {
        return BaseIO::Connect(linkable);
    }
    return nullptr;
}

Output::Output(QQuickItem *parent) :
    IO(parent)
{

}

void Output::refreshBackendIO()
{
//    if (m_io)
//        delete m_io;
    m_io = new OutputBackend(m_type);
}
