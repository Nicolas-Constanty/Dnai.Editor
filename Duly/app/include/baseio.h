#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "iotype.h"

namespace duly_gui {

    class BaseIo : public BaseLinkable
    {
    public:
        BaseIo(IoTypeRessouce::IoType type, QQuickItem *parent);
        ~BaseIo();

        /**
         * \brief set the IOType
         * \param t
         */
        void setType(IoTypeRessouce::IoType t);

        /**
        * \brief return the IOType
        */
        IoTypeRessouce::IoType getType() const;


    protected:
        IoTypeRessouce::IoType m_type;

    };
}



#endif // BASEIO_H
