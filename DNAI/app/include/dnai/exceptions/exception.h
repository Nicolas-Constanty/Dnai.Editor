#ifndef DNAI_EXECPTIONS_EXCEPTION_H
#define DNAI_EXECPTIONS_EXCEPTION_H
#include <stdexcept>

namespace dnai
{
	namespace exceptions
	{
		class Exception : public std::runtime_error
		{
		public:
			explicit Exception(const std::string& _Message, const std::string& from = "")
				: runtime_error("DNAI Exception " + (!from.empty() ? "from (" + from + ") :" : ":") + _Message)
			{
			}
			~Exception() override = default;
		};
	}
}

#endif //DNAI_EXECPTIONS_EXCEPTION_H