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
	return l;
}

void BaseLinkable::unlink(ALinkable *linkable)
{
	const auto l = getLink(linkable);
	if (l != nullptr)
	{
		m_links.removeOne(l);
		linkable->removeLink(l);
	}
	//TODO INSERT DEBUG "Link doesn't exist"
}

void BaseLinkable::unlinkAll()
{
	auto l = m_links;
	for (auto i : l)
	{
		i->L2->unlink(this);
	}
	m_links.clear();
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
	auto ref = m_links;
	const auto findFunc = [&](auto *l) {
		return ((l->L1 == this && l->L2 == linkable) || (l->L1 == linkable && l->L2 == this));
	};
	const auto it = std::find_if(ref.begin(), ref.end(), findFunc);
	if (it == ref.end()) return nullptr;
	return (*it);
}
