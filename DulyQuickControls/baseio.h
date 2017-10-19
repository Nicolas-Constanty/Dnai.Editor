#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "resourcesnode.h"

class BaseIo : public BaseLinkable
{
public:
    BaseIo(DulyResources::IOType type, QQuickItem *parent);
    ~BaseIo();

	/**
	 * \brief set the IOType
	 * \param t 
	 */
	void setType(DulyResources::IOType t);

	/**
	* \brief return the IOType
	*/
	DulyResources::IOType getType() const;


protected:
    DulyResources::IOType m_type;

};

#endif // BASEIO_H
