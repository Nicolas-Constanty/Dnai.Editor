#ifndef DNAI_EXCEPTION_NOT_IMPLEMENTED_H
#define DNAI_EXCEPTION_NOT_IMPLEMENTED_H

#include "dnai/exceptions/exception.h"

#include <QDebug>
namespace dnai
{
	namespace exceptions
	{
        class NotImplemented : public Exception
		{
		public:
            NotImplemented() : Exception("Function not yet implemented") {
                qCritical() << "Function not yet implemented";
            }
		};
	}
}

#endif //DNAI_EXCEPTION_NOT_IMPLEMENTED_H
