#include <QJsonArray>
#include <QHttpMultiPart>

#include "dnai/api/api.h"
#include "dnai/app.h"
#include "dnai/http/service.h"

namespace dnai {
const QString api::client_id = "";
const QString api::client_secret = "";
api::User api::user = {};
bool api::rememberUser = false;
bool api::refreshing_token = false;
quint64 api::refreshing_delta = 3600;
const QString api::settings_key = "/current/user";
const http::Config api::http_config = {
    "https://api.preprod.dnai.io/",
      {},
      {
        [](http::Url *url) {
            auto token = getToken();
            if (!token.isEmpty()) {
                url->addHeader("Authorization", "Bearer " + token);
            }
        },
        [](http::Url *url) {
            Q_UNUSED(url)
            if (api::refreshing_token == false && QDateTime::currentDateTime().addSecs(api::refreshing_delta) >= api::user.expire_date) {
                api::refresh_token();
            }
        }
    }
  };

    http::Observable &api::signin(const QString &login, const QString &password)
    {
        return http::Service::url("signin")
                ->headers(
                    http::Headers{
                    //    {"Authorization", "Basic " + QString(client_id + ":" + client_secret).toUtf8().toBase64()},
                        {"Content-Type", "application/json"}
                    })
                ->post(QJsonObject{
                          // {"grant_type", "password"},
                           {"login", login},
                           {"password", password}
                       })
                .map([](http::Response response) -> http::Response {
            api::setUser({
                response.body["token"].toString(),
                response.body["refreshToken"].toString(),
                response.body["user_id"].toString(),
                QDateTime::currentDateTime().addSecs(6000000)
            });
            return response;
        });
    }

    http::Observable &api::refresh_token()
    {
        qDebug() << "REFRESHTOKEN: " << api::user.refresh_token;
        api::refreshing_token = true;
        return http::Service::url("refresh")
                ->headers(
                    http::Headers{
                       // {"Authorization", "Basic " + QString(client_id + ":" + client_secret).toUtf8().toBase64()},
                        {"Content-Type", "application/json"}
                    })
                ->post(QJsonObject{
                          // {"grant_type", "refresh_token"},
                           {"refreshToken", api::user.refresh_token}
                       })
                .map([](http::Response response) -> http::Response {
            api::setUser({
                             response.body["token"].toString(),
                             response.body["refreshToken"].toString(),
                             response.body["user_id"].toString(),
                             QDateTime::currentDateTime().addSecs(6000000)
            });
            api::refreshing_token = false;
            return response;
        });
    }

    http::Observable &api::get_current_user()
    {
        //TODO when API work `/users/me` and remove John Doe
        return http::Service::url("users", api::user.id.toLatin1().data())->get().map([](http::Response response) -> http::Response {

            return response;
        });
    }

    http::Observable &api::get_files()
    {
        return http::Service::url("files")->get();
    }

    http::Observable &api::get_download_object(QString const &platform, QString const &slug)
    {
        return http::Service::url("download/softwares", platform.toLatin1().data(), slug.toLatin1().data())->get();
    }

    http::Observable &api::get_file(QString const &id)
    {
        return http::Service::url("files", id.toLatin1().data())->get();
    }

    http::Observable &api::get_raw_file(QString const &id)
    {
        return http::Service::url("uploaded_files", id.toLatin1().data())->get();
    }

    http::Observable &api::post_file(QString const &title, QFile *file)
    {
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        multiPart->append(http::Service::makeHttpPart("file_type_id", "1"));
        multiPart->append(http::Service::makeHttpPart("title", title));
        multiPart->append(http::Service::makeHttpPart("file", file));
        file->setParent(multiPart);

        return http::Service::url("files")->post(multiPart);
    }

    void api::logout()
    {
        api::user = {};
        App::currentInstance()->settings().setAPIValue(api::settings_key, QVariant::fromValue(api::user));
    }

    QString const &api::getToken()
    {
        return user.token;
    }

    QString const &api::getId() {
        return user.id;
    }

    void api::setUser(const api::User &user)
    {
        api::user = user;
        if (api::rememberUser)
            App::currentInstance()->settings().setAPIValue(api::settings_key, QVariant::fromValue(api::user));
    }
}

QDataStream &operator<<(QDataStream &out, const dnai::api::User &v)
{
    out << v.token << v.refresh_token << v.id << v.expire_date;
    return out;
}

QDataStream &operator>>(QDataStream &in, dnai::api::User &v)
{
    in >> v.token;
    in >> v.refresh_token;
    in >> v.id;
    in >> v.expire_date;
    return in;
}
