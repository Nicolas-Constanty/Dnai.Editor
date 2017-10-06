#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "output.h"
#include "input.h"
#include "link.h"
#include "genericnode.h"
#include "dulycanvas.h"

InputBackend::InputBackend(DulyResources::IOType t, QQuickItem *parent)
	: BaseIo(t, parent)
{
}

Link *InputBackend::connect(ALinkable *linkable, BezierCurve *curve)
{
    const auto li = dynamic_cast<OutputBackend *>(linkable);
    if (li != nullptr && li->getType() == getType())
    {
        auto l = getLink(linkable);
        if (l == nullptr)
        {
            m_links.clear();
            l = new Link(this, linkable);
            l->setCurve(curve);
            m_links.append(l);
            linkable->addLink(l);
            return l;
        }
        //TODO INSERT DEBUG "Link already exist"
        return l;
    }
    return nullptr;
}

Input::Input(QQuickItem *parent) :
    Io(parent)
{
    m_io = new InputBackend(m_type, this);
}

void Input::refreshBackendIo()
{
    m_io = new InputBackend(m_type, this);
}

void Input::componentComplete()
{
    QQuickItem::componentComplete();
	auto n = dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
    n->inputs().registerItem(this);
}

Io *Input::findIo(GenericNode *n, const QPointF &p)
{
    auto qlist = n->outputs().findFocused(p);
    return (qlist.size() != 0)?dynamic_cast<Io*>(qlist.at(0)):nullptr;
}

void Input::updateLink()
{
    auto list = m_io->links();
	for (auto i = 0; i < list.size(); i++)
    {
		const auto l = list.at(i);
		l->curve()->setPosition(mapToItem(DulyCanvas::Instance, position() + QPointF(width() / 2, height() / 2)));
        const auto io = dynamic_cast<Output *>(dynamic_cast<BaseIo *>(l->L1 != m_io?l->L1:l->L2)->parent());
        l->curve()->setP4(
                    io->parentItem()->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->parentItem()->position() +
                    io->parentItem()->parentItem()->position() +
                    io->parentItem()->position() + io->position() + QPointF(io->width() / 2, io->height() / 2)
                    );
	}
}
