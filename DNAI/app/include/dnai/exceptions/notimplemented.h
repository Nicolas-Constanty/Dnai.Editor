#ifndef DNAI_EXCEPTION_NOT_IMPLEMENTED_H
#define DNAI_EXCEPTION_NOT_IMPLEMENTED_H
#include <stdexcept>

namespace dnai
{
	namespace exceptions
	{
		class NotImplemented : public std::logic_error
		{
		public:
			NotImplemented() : std::logic_error("Function not yet implemented") { };
		};
	}
}

#endif //DNAI_EXCEPTION_NOT_IMPLEMENTED_H