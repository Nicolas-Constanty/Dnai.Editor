#include "baseio.h"

namespace duly_gui
{
    BaseIo::BaseIo(DulyResources::IoType type, QQuickItem *parent) : BaseLinkable(parent), m_type(type)
	{
	}

	BaseIo::~BaseIo()
	{

	}

    void BaseIo::setType(DulyResources::IoType t)
	{
		if (t == m_type)
			return;
		m_type = t;
	}

    DulyResources::IoType BaseIo::getType() const
	{
		return m_type;
	}
}
