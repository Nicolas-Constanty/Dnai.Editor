#ifndef DNAI_INTERFACES_ISINGLETON_H
#define DNAI_INTERFACES_ISINGLETON_H

namespace dnai
{
	namespace interfaces
	{
		template<class T>
		class ISingleton
		{
		protected:
			ISingleton() = default;

		public:
			// delete copy and move constructors and assign operators
			ISingleton(ISingleton const&) = delete;             // Copy construct
			ISingleton(ISingleton&&) = delete;                  // Move construct
			ISingleton& operator=(ISingleton const&) = delete;  // Copy assign
			ISingleton& operator=(ISingleton &&) = delete;      // Move assign
			virtual ~ISingleton() = default;
			static T *instance()
			{
				if (m_instance == nullptr)
					m_instance = new T();
				return m_instance;
			}

		private:
			T *m_instance = nullptr;
		};
	}
}

#endif DNAI_INTERFACES_ISINGLETON_H