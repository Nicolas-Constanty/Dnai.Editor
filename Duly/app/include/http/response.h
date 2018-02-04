#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

namespace duly_gui {
    namespace  http {
        struct Status {
          int code;
          QString message;
        };
        struct Response {
            Status status;
            QJsonObject body;
            operator QString() const;
        };
    }
}

#endif // HTTP_RESPONSE_H
