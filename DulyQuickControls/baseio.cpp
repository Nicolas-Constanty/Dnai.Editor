#include "link.h"
#include "baseio.h"
#include <QDebug>

BaseIo::BaseIo(DulyResources::IOType type, QQuickItem *parent) : BaseLinkable(parent), m_type(type)
{
}

BaseIo::~BaseIo()
{

}

void BaseIo::setType(DulyResources::IOType t)
{
    if (t == m_type)
        return;
    m_type = t;
}

DulyResources::IOType BaseIo::getType() const
{
	return m_type;
}
