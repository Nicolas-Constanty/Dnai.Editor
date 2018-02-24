#ifndef IFACTORY_H
#define IFACTORY_H

#include <map>
#include <functional>
#include <type_traits>

template <typename FactoryType, class ClassIdentifier>
class IFactory
{
    using Callback = std::function<void *()>;
    using Key = typename std::conditional<std::is_enum<ClassIdentifier>::value, int, ClassIdentifier>::type;
public:
	IFactory() = default;
        FactoryType *create(Key ci)
        {
            void *result = m_factoryObjects[ci]();
            return reinterpret_cast<FactoryType *>(result);
        }

        template<typename TrueType, typename ... Args>
    void registerObject(Key ci, Args&& ... args)
        {
            m_factoryObjects[ci] = [=]() { return static_cast<void *>(new TrueType(std::move(args)...)); };
	}

private:
        std::map<Key, Callback> m_factoryObjects;
};

#endif //IFACTORY_H
