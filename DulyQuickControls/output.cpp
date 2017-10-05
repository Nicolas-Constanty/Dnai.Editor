#include <QtQuick/qsgflatcolormaterial.h>
#include <QtMath>

#include "output.h"
#include "input.h"

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
    m_io = new OutputBackend(m_type);
}

void Output::refreshBackendIo()
{
    m_io = new OutputBackend(m_type);
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
