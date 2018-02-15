#ifndef BASEIO_H
#define BASEIO_H

#include "baselinkable.h"
#include "qmlresources/iotype.h"

namespace dnai {
    class BaseIo : public BaseLinkable
    {
    public:
        BaseIo(qmlresources::IoTypeRessouce::IoType type, QQuickItem *parent);
        ~BaseIo();

        /**
         * \brief set the IOType
         * \param t
         */
        void setType(qmlresources::IoTypeRessouce::IoType t);

        /**
        * \brief return the IOType
        */
        qmlresources::IoTypeRessouce::IoType getType() const;


    protected:
        qmlresources::IoTypeRessouce::IoType m_type;

    };
}



#endif // BASEIO_H
