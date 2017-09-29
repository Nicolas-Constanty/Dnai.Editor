#ifndef ILINKABLE_H
#define ILINKABLE_H

#include <memory>
#include "observablelist.h"

class Link;

class ILinkable
{
public:
	virtual ~ILinkable() = default;

    virtual void UnlinkAll() = 0;

    virtual bool IsLink() = 0;
};

class ALinkable : public ILinkable
{
public:
    virtual ~ALinkable() {
        m_links.Clear();
    }
    const ObservableList<std::shared_ptr<Link>> &Links() const { return m_links; }
    virtual const std::shared_ptr<Link> &Connect(ALinkable *linkable) = 0;
    virtual void Unlink(ALinkable *linkable) = 0;
	void UnlinkAll() override = 0;
	virtual void AddLink(const std::shared_ptr<Link> &l) = 0;
	virtual void RemoveLink(const std::shared_ptr<Link> &l) = 0;

	bool IsLink() override = 0;

    virtual const std::shared_ptr<Link> &GetLink(ALinkable *linkable) const = 0;

protected:
    ObservableList<std::shared_ptr<Link>> m_links;
};

#endif // ILINKABLE_H
