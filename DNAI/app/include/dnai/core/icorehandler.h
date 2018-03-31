#ifndef DNAI_CORE_ICOREHANDLER_H
#define DNAI_CORE_ICOREHANDLER_H

namespace dnai
{
    namespace core
    {
        class ICoreHandler
        {
        public:
            virtual ~ICoreHandler() = default;

        public:
            virtual void setup() = 0;
        };
    }
}

#endif // DNAI_CORE_ICOREHANDLER_H
