#ifndef DNAI_INTERFACES_IFACTORY_H
#define DNAI_INTERFACES_IFACTORY_H

#include <map>
#include <functional>
#include <type_traits>

namespace dnai {
    namespace interfaces {
	    /**
         * \brief This class allow you to create a factory for anytype of the Base class (FactoryType) with anytype of identifier (ClassIdentifier)
         * \tparam FactoryType 
         * \tparam ClassIdentifier 
         */
        template <typename FactoryType, class ClassIdentifier>
        class IFactory
        {
            using Callback = std::function<FactoryType *()>;
            using Key = typename std::conditional<std::is_enum<ClassIdentifier>::value, int, ClassIdentifier>::type;
        public:
            IFactory() = default;
	        /**
                 * \brief Return a new instance of type (FactoryType) with the identifier of type (ClassIdentifier)
                 * \param ci 
                 * \return return the new instance of object or nullptr if an error occur
                 */
                FactoryType *create(Key ci)
                {
                    return m_factoryObjects[ci]();
                }

	        /**
                 * \brief Register a new class of type (TrueType) witch derived of base type (FactoryType) and assign an identifier of type ClassIdentifier
                 * \tparam TrueType 
                 * \tparam Args 
                 * \param ci 
                 * \param args 
                 */
                template<typename TrueType, typename ... Args>
            void registerObject(Key ci, Args&& ... args)
            {
                m_factoryObjects[ci] = [=]() { return static_cast<FactoryType *>(new TrueType(std::move(args)...)); };
            }

        private:
                std::map<Key, Callback> m_factoryObjects;
        };
    }
}


#endif //DNAI_INTERFACES_IFACTORY_H
