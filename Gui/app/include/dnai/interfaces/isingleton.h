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
       //                 static T &instance()
       //                 {
							////return reinterpret_cast<T *>()
       //                 }
                protected:
					void *m_instance;
                };
        }
}

#endif // DNAI_INTERFACES_ISINGLETON_H
