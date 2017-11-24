#include "baseio.h"

namespace duly_gui
{
    BaseIo::BaseIo(IoType type, QQuickItem *parent) : BaseLinkable(parent), m_type(type)
	{
	}

	BaseIo::~BaseIo()
	{

	}

    void BaseIo::setType(IoType t)
	{
		if (t == m_type)
			return;
		m_type = t;
	}

    IoType BaseIo::getType() const
	{
		return m_type;
	}
}
