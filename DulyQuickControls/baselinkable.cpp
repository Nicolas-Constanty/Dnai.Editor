#include "link.h"
#include "baselinkable.h"
#include <QDebug>

BaseLinkable::BaseLinkable(QQuickItem *parent)
{
	m_parent = parent;
}

BaseLinkable::~BaseLinkable()
{

}

Link *BaseLinkable::connect(ALinkable *linkable, BezierCurve *curve)
{
    auto l = getLink(linkable);
	if (l == nullptr)
	{
		l = new Link(this, linkable);
		l->setCurve(curve);
		m_links.append(l);
		linkable->addLink(l);
		return l;
	}
	//TODO INSERT DEBUG "Link already exist"
    return nullptr;
}

void BaseLinkable::unlink(ALinkable *linkable)
{
    const auto l = getLink(linkable);
    if (l != nullptr)
    {
        m_links.removeOne(l);
        delete l;
    }
    m_links.removeAll(nullptr);
	//TODO INSERT DEBUG "Link doesn't exist"
}

void BaseLinkable::unlinkAll()
{
    while (!m_links.empty()) {
        auto l = m_links.back();
        if (l->L1 != this)
        {
            l->L1->unlink(this);
            m_links.removeOne(l);
        }
        else
        {
            l->L2->unlink(this);
            m_links.removeOne(l);
        }
    }
}

void BaseLinkable::addLink(Link *l)
{
	m_links.append(l);
}

void BaseLinkable::removeLink(Link *l)
{
	m_links.removeOne(l);
}

bool BaseLinkable::isLink()
{
    return !m_links.empty();
}

Link *BaseLinkable::getLink(ALinkable *linkable) const
{
    for (auto i = 0; i < m_links.size(); i++)
    {
        auto l = m_links.at(i);
        if ((l->L1 == this && l->L2 == linkable) || (l->L1 == linkable && l->L2 == this))
            return l;
    }
    return nullptr;
}
