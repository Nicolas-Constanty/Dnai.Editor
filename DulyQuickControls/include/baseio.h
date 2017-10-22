#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "resourcesnode.h"

namespace duly_gui {

    class BaseIo : public BaseLinkable
    {
    public:
        BaseIo(DulyResources::IoType type, QQuickItem *parent);
        ~BaseIo();

        /**
         * \brief set the IOType
         * \param t
         */
        void setType(DulyResources::IoType t);

        /**
        * \brief return the IOType
        */
        DulyResources::IoType getType() const;


    protected:
        DulyResources::IoType m_type;

    };
}



#endif // BASEIO_H
