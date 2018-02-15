#include "dnai/baseio.h"

namespace dnai
{
    BaseIo::BaseIo(qmlresources::IoTypeRessouce::IoType type, QQuickItem *parent) : BaseLinkable(parent), m_type(type)
	{
	}

	BaseIo::~BaseIo()
	{

	}

    void BaseIo::setType(qmlresources::IoTypeRessouce::IoType t)
	{
		if (t == m_type)
			return;
		m_type = t;
	}

    qmlresources::IoTypeRessouce::IoType BaseIo::getType() const
	{
		return m_type;
	}
}
