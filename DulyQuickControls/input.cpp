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
            if (m_links.size() > 0)
            {
                unlinkAll();
            }
            l = new Link(this, linkable);
            l->setCurve(curve);
            return l;
        }
        //TODO INSERT DEBUG "Link already exist"
        return nullptr;
    }
    return nullptr;
}

Input::Input(QQuickItem *parent) :
    Io(parent)
{
    m_linkable = new InputBackend(m_type, this);
}

void Input::refreshBackendIo()
{
    m_linkable = new InputBackend(m_type, this);
}

void Input::componentComplete()
{
    QQuickItem::componentComplete();
    auto n = dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
    n->inputs().registerItem(this);
}

LinkableBezierItem* Input::findLinkableBezierItem(GenericNode* n, const QPointF& p)
{
    auto qlist = n->outputs().findFocused(p);
    return (qlist.size() != 0) ? dynamic_cast<Io*>(qlist.at(0)) : nullptr;
}

void Input::updateLink()
{
    auto list = m_linkable->links();
    for (auto i = 0; i < list.size(); i++)
    {
        const auto l = list.at(i);
        l->curve()->setRealPosition(getCanvasPos());
        const auto io = dynamic_cast<Output *>(dynamic_cast<BaseIo *>(l->L1 != m_linkable ?l->L1:l->L2)->parent());
        l->curve()->setP4(io->getCanvasPos());
    }
}

void Input::afterRealease(Link *l)
{
    if (l == nullptr)
        unlinkAll();
}
