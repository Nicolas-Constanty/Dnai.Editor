#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "output.h"
#include "input.h"
#include "link.h"
#include "genericnode.h"
#include "dulycanvas.h"

OutputBackend::OutputBackend(DulyResources::IOType type, QQuickItem* parent) 
: BaseIo(type, parent)
{
}

Link *OutputBackend::connect(ALinkable *linkable, BezierCurve *curve)
{
	const auto li = dynamic_cast<InputBackend *>(linkable);

    if (li != nullptr && li->getType() == getType())
    {
        return BaseIo::connect(linkable, curve);
    }
    return nullptr;
}

Output::Output(QQuickItem *parent) :
    Io(parent)

{
    m_io = new OutputBackend(m_type, this);
}

void Output::refreshBackendIo()
{
    m_io = new OutputBackend(m_type, this);
}

void Output::componentComplete()
{
    QQuickItem::componentComplete();
	auto n = dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
    n->outputs().registerItem(this);
}

Io *Output::findIo(GenericNode *n, const QPointF &p)
{
    auto qlist = n->inputs().findFocused(p);
    return (qlist.size() != 0)?dynamic_cast<Io*>(qlist.at(0)):nullptr;
}

void Output::updateLink()
{
    auto list = m_io->links();
    for (auto i = 0; i < list.size(); i++)
    {
        const auto l = list.at(i);
        l->curve()->setPosition(mapToItem(DulyCanvas::Instance, position() + QPointF(width() / 2, height() / 2)));
        const auto io = dynamic_cast<Input *>(dynamic_cast<BaseIo *>(l->L1 != m_io?l->L1:l->L2)->parent());
        l->curve()->setP4(
                    io->parentItem()->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->position() +
                    io->parentItem()->position() + io->position() + QPointF(io->width() / 2, io->height() / 2)
                    );
    }
}
