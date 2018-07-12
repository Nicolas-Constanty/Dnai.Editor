#ifndef API_API_H
#define API_API_H

#include <QString>
#include <QFile>
#include "dnai/http/observable.h"
#include "dnai/http/config.h"
#include "dnai/http/types.h"

//using namespace dnai::http;


namespace dnai {
    class  api {
    public:
        struct User {
            QString token;
            QString refresh_token;
            QString id;
            QDateTime expire_date;
        };

    public:
        static const http::Config http_config;
        static const QString settings_key;
        static bool rememberUser;

    public:
        static bool refreshing_token;
        static quint64 refreshing_delta;

    public:
        static const QString client_id;
        static const QString client_secret;
        static User user;

    public:
        static QString const &getToken();
        static QString const &getId();
        static void setUser(User const &);

    public:
        static http::Observable &signin(QString const &, QString const &);
        static http::Observable &refresh_token();
        static http::Observable &get_current_user();
        static http::Observable &get_files();
        static http::Observable &get_file(QString const &);
        static http::Observable &get_raw_file(QString const &);
        static http::Observable &post_file(QString const &, QFile *);
        static http::Observable &get_download_object(QString const &platform, QString const &slug);
        static void logout();
    };
}

Q_DECLARE_METATYPE(dnai::api::User)

QDataStream& operator<<(QDataStream& out, const dnai::api::User& v);

QDataStream& operator>>(QDataStream& in, dnai::api::User& v);

#endif // API_API_H
