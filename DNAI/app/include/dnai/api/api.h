#ifndef API_API_H
#define API_API_H

#include <QString>
#include <QFile>
#include "dnai/http/observable.h"
#include "dnai/http/config.h"
#include "dnai/http/types.h"

using namespace dnai::http;

namespace dnai {
    class  api {
    public:
        struct User {
            QString token;
            QString refresh_token;
            QDateTime expire_date;
        };

    public:
        static const Config http_config;
        static const QString settings_key;

    private:
        static const QString client_id;
        static const QString client_secret;
        static User user;

    public:
        static QString const &getToken();
        static void setUser(User const &);

    public:
        static Observable &signin(QString const &, QString const &);
        static Observable &refresh_token();
        static Observable &get_current_user();
        static Observable &get_files();
        static Observable &get_file(QString const &);
        static Observable &get_raw_file(QString const &);
        static Observable &post_file(QString const &, QFile *);
        static void logout();
    };
}

Q_DECLARE_METATYPE(dnai::api::User)

QDataStream& operator<<(QDataStream& out, const dnai::api::User& v);

QDataStream& operator>>(QDataStream& in, dnai::api::User& v);

#endif // API_API_H
