#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "output.h"
#include "input.h"
#include "link.h"
#include "genericnode.h"

InputBackend::InputBackend(DulyResources::IOType t): BaseIo()
{
	m_type = t;
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
            m_links.add(l);
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
    m_io = new InputBackend(m_type);
}

void Input::refreshBackendIo()
{
    m_io = new InputBackend(m_type);
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
