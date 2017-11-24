#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "resourcesnode.h"

namespace duly_gui {

    class BaseIo : public BaseLinkable
    {
    public:
        BaseIo(IoType type, QQuickItem *parent);
        ~BaseIo();

        /**
         * \brief set the IOType
         * \param t
         */
        void setType(IoType t);

        /**
        * \brief return the IOType
        */
        IoType getType() const;


    protected:
        IoType m_type;

    };
}



#endif // BASEIO_H
