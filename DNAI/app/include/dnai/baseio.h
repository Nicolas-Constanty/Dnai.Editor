#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "enums/iotype.h"

namespace dnai {
    class BaseIo : public BaseLinkable
    {
    public:
        BaseIo(enums::IoTypeRessouce::IoType type, QQuickItem *parent);
        ~BaseIo();

        /**
         * \brief set the IOType
         * \param t
         */
        void setType(enums::IoTypeRessouce::IoType t);

        /**
        * \brief return the IOType
        */
        enums::IoTypeRessouce::IoType getType() const;


    protected:
        enums::IoTypeRessouce::IoType m_type;

    };
}



#endif // BASEIO_H
