#include "dnai/baseio.h"

namespace dnai
{
    BaseIo::BaseIo(enums::IoTypeRessouce::IoType type, QQuickItem *parent) : BaseLinkable(parent), m_type(type)
	{
	}

	BaseIo::~BaseIo()
	{

	}

    void BaseIo::setType(enums::IoTypeRessouce::IoType t)
	{
		if (t == m_type)
			return;
		m_type = t;
	}

    enums::IoTypeRessouce::IoType BaseIo::getType() const
	{
		return m_type;
	}
}
