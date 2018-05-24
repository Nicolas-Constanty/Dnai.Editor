#include  <stdexcept>
#include "dnai/link.h"
#include "dnai/views/beziercurve.h"

namespace dnai
{
	Link::Link() : L1(nullptr), L2(nullptr), m_bezierCurve(nullptr)
	{
	}

	void Link::ClearLink()
	{
		L1->removeLink(this);
		L2->removeLink(this);
		delete this;
	}

	Link::~Link()
	{

		if (m_bezierCurve)
			delete m_bezierCurve;
	}

    Link::Link(interfaces::ALinkable *l1, interfaces::ALinkable *l2) : m_bezierCurve(nullptr)
	{
		if (l1 == l2)
			std::runtime_error("L1 and L2 cannot be the same object!");
		L1 = l1;
		L2 = l2;
		L1->addLink(this);
		L2->addLink(this);
	}
}
