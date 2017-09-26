#ifndef BASEIO_H
#define BASEIO_H

#include <memory>

#include "ilinkable.h"
#include "resourcesnode.h"

class BaseIO : public ALinkable
{
public:
    BaseIO();
    ~BaseIO();

	const std::shared_ptr<Link> &Connect(ALinkable *linkable) override;
	void Unlink(ALinkable *linkable) override;
	void UnlinkAll() override;
	void AddLink(const std::shared_ptr<Link> &l) override;
	void RemoveLink(const std::shared_ptr<Link> &l) override;
    void setType(DulyResources::IOType t);
    DulyResources::IOType GetType() const { return m_type; }

    bool IsLink() override;

	const std::shared_ptr<Link> &GetLink(ALinkable *linkable) const override;

protected:
    DulyResources::IOType m_type;
};

#endif // BASEIO_H
