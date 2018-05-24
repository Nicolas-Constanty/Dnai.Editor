#ifndef DNAI_INTERFACES_ISCALABLE_H
#define DNAI_INTERFACES_ISCALABLE_H

#include <QPointF>

namespace dnai
{
    namespace interfaces {
	    /**
         * \brief This interface allow to create custom scale for inherited object
         */
        class IScalable
        {
        public:
	        /**
             * \brief Return the current scale factor
             * \return 
             */
            virtual qreal scaleFactor() const = 0;
	        /**
             * \brief Return the position with scale aplyed
             * \return 
             */
            virtual QPointF scalePos() const = 0;

	        /**
             * \brief Return the position without the scale applyed
             * \return 
             */
            virtual QPointF realPos() const = 0;
        };
    }
}

#endif // DNAI_INTERFACES_ISCALABLE_H
