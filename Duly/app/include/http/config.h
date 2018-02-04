#ifndef HTTP_CONFIG_H
#define HTTP_CONFIG_H

#include <string>
#include "types.h"

namespace duly_gui {
    namespace  http {
        struct Config {
            std::string base_url;
            Headers headers;
            QList<InterceptorFunction> interceptors;
        };
    }
}

#endif // HTTP_CONFIG_H
