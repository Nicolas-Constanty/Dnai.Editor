#include "link.h"
#include "baseio.h"

BaseIO::BaseIO() : m_type(DulyResources::IOType::Int)
{

}

BaseIO::~BaseIO()
{

}

const std::shared_ptr<Link> &BaseIO::Connect(ALinkable *linkable)
{
    auto l = GetLink(linkable);
    if (l.get() == nullptr)
    {
        l = std::make_shared<Link>(this, linkable);
        m_links.Add(l);
		linkable->AddLink(l);
        return l;
    }
    //TODO INSERT DEBUG "Link already exist"
    return l;
}

void BaseIO::Unlink(ALinkable *linkable)
{
	const auto l = GetLink(linkable);
    if (l != nullptr)
    {
		m_links.Remove(l);
        linkable->RemoveLink(l);
    }
    //TODO INSERT DEBUG "Link doesn't exist"
}

void BaseIO::UnlinkAll()
{
    auto l = m_links.rawList();
    for (auto i : l)
    {
        i->L2->Unlink(this);
    }
    m_links.Clear();
}

void BaseIO::AddLink(const std::shared_ptr<Link>& l)
{
	m_links.Add(l);
}

void BaseIO::RemoveLink(const std::shared_ptr<Link>& l)
{
	m_links.Remove(l);
}

bool BaseIO::IsLink()
{
    return m_links.Empty();
}

void BaseIO::setType(DulyResources::IOType t)
{
    if (t == m_type)
        return;
    m_type = t;
}

const std::shared_ptr<Link> &BaseIO::GetLink(ALinkable *linkable) const
{
    auto ref = m_links.rawList();
	const auto findFunc = [&](const std::shared_ptr<Link> l){
        return ((l->L1 == this && l->L2 == linkable) || (l->L1 == linkable && l->L2 == this));
    };
    return *std::find_if(ref.begin(), ref.end(), findFunc);
}
