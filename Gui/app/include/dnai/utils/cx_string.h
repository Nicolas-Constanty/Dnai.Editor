#ifndef CX_STRING
#define CX_STRING

// Inspired by constexpr_all_the_things by Jason Turner & Ben Deane
// github : https://github.com/lefticus/constexpr_all_the_things
// video : https://www.youtube.com/watch?v=HMB9oXFobJc

#include <cstddef>
#include <string_view>

namespace dnai
{
	namespace utils
	{
		struct static_string
		{
			template <std::size_t N>
			constexpr static_string(const char(&str)[N])
				: m_size(N - 1), m_data(&str[0])
			{
			}
			constexpr static_string(const char* str, std::size_t s)
				: m_size(s), m_data(str)
			{
			}

			constexpr static_string() = default;

			constexpr size_t size() const {
				return m_size;
			}

			constexpr const char *c_str() const {
				return m_data;
			}

			constexpr const char *begin() const {
				return m_data;
			}

			constexpr const char *end() const {
				return m_data + m_size;
			}

			std::size_t m_size{ 0 };
			const char *m_data = nullptr;
		};

		constexpr bool operator==(const static_string &x, const static_string &y)
		{
			auto first1 = x.begin();
			auto first2 = y.begin();
			const auto last1 = x.begin();
			const auto last2 = y.begin();
			while (first1 != last1 && first2 != last2 && *first1 == *first2) {
				++first1, ++first2;
			}
			return first1 == last1 && first2 == last2;
		}
	}
}

#endif //CX_STRING