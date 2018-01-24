#ifndef API_API_H
#define API_API_H

#include <QString>
#include "http/observable.h"
#include "http/config.h"
#include "http/types.h"

using namespace duly_gui::http;

namespace duly_gui {
    class  api {
        struct User {
            QString token;
            QString refresh_token;
            QDateTime expire_date;
        };

    public:
        static const Config http_config;

    private:
        static const QString client_id;
        static const QString client_secret;
        static User user;

    public:
        static QString const &getToken();

    public:
        static Observable &signin(QString const &, QString const &);
        static void logout();

    };
}

#endif // API_API_H
