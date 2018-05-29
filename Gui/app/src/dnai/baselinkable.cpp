#include <QDebug>
#include "dnai/baselinkable.h"
#include "dnai/link.h"

namespace dnai
{
	BaseLinkable::BaseLinkable(QQuickItem *parent)
	{
		m_parent = parent;
	}

	BaseLinkable::~BaseLinkable()
	{

	}

    Link *BaseLinkable::connect(ALinkable *linkable, views::BezierCurve *curve)
	{
		auto l = getLink(linkable);
		if (l == nullptr)
		{
			l = new Link(this, linkable);
			l->setCurve(curve);
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
			l->ClearLink();
		}
		m_links.removeAll(nullptr);
		//TODO INSERT DEBUG "Link doesn't exist"
	}

	void BaseLinkable::unlinkAll()
	{
        //TODO CORE UNLINK_ALL
		while (!m_links.empty()) {
			auto l = m_links.back();
			l->ClearLink();
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
			const auto l = m_links.at(i);
			if ((l->L1 == this && l->L2 == linkable) || (l->L1 == linkable && l->L2 == this))
				return l;
		}
		return nullptr;
	}

}
