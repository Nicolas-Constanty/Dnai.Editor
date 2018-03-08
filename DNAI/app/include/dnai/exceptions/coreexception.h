#ifndef DNAI_EXECPTIONS_COREEXECPTION_H
#define DNAI_EXECPTIONS_COREEXECPTION_H
#include "exception.h"

namespace dnai
{
	namespace exceptions
	{
		class CoreExeption : public Exception
		{
		public:
			explicit CoreExeption(const std::string& _Message)
				: Exception(_Message, "Core")
			{
			}
		};
	}
}

#endif //DNAI_EXECPTIONS_COREEXECPTION_H