#include  <stdexcept>
#include "link.h"
#include "views/beziercurve.h"

namespace duly_gui
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

	Link::Link(ALinkable *l1, ALinkable *l2) : m_bezierCurve(nullptr)
	{
		if (l1 == l2)
			std::runtime_error("L1 and L2 cannot be the same object!");
		L1 = l1;
		L2 = l2;
		L1->addLink(this);
		L2->addLink(this);
	}
}
