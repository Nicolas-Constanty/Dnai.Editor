#ifndef HTTP_TYPES_H
#define HTTP_TYPES_H

#include <QMap>

namespace duly_gui {
    namespace  http {
        class Url;
        typedef QMap<QString, QString> Headers;
        typedef QMap<QString, QString> Params;
        typedef QMap<QString, QString> Form;
        typedef std::function<void (Url*)> InterceptorFunction;
    }
}
#endif // TYPES_H
