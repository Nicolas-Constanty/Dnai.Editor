#include <QUrlQuery>
#include <QJsonDocument>
#include "dnai/http/url.h"

namespace dnai {
    namespace  http {
        Url::Url(QNetworkAccessManager *manager, QUrl const &url)
            : QObject (nullptr), m_manager(manager), m_url(url) {

        }

        Observable &Url::head()
        {
            m_method = "HEAD";
            return sendRequest();
        }

        Observable &Url::get()
        {
            m_method = "GET";
            return sendRequest();
        }

        Observable &Url::post(QByteArray body)
        {
            m_body = body;
            m_method = "POST";
            return sendRequest();
        }

        Observable &Url::post(QJsonObject body)
        {
            return post(QJsonDocument(body).toJson());
        }

        Observable &Url::post(Form body)
        {
            QUrlQuery query;

            for (auto it = body.begin(); it != body.end(); ++it) {
                query.addQueryItem(it.key(), it.value());
            }
            return post(query.query(QUrl::FullyEncoded).toUtf8());
        }

        Observable &Url::post(QHttpMultiPart *multiPart)
        {
            m_multiPart = multiPart;
            m_bodyType = MULTIPART;
            m_method = "POST";
            return sendRequest();
        }

        Observable &Url::post(QIODevice *device)
        {
            m_device = device;
            m_bodyType = DEVICE;
            m_method = "POST";
            return sendRequest();
        }

        Observable &Url::put(QByteArray body)
        {
            m_body = body;
            m_method = "PUT";
            return sendRequest();
        }

        Observable &Url::put(QJsonObject body)
        {
            return put(QJsonDocument(body).toJson());
        }

        Observable &Url::put(Form body)
        {
            QUrlQuery query;

            for (auto it = body.begin(); it != body.end(); ++it) {
                query.addQueryItem(it.key(), it.value());
            }
            return put(query.query(QUrl::FullyEncoded).toUtf8());
        }

        Observable &Url::put(QHttpMultiPart *multiPart)
        {
            m_multiPart = multiPart;
            m_bodyType = MULTIPART;
            m_method = "PUT";
            return sendRequest();
        }

        Observable &Url::put(QIODevice *device)
        {
            m_device = device;
            m_bodyType = DEVICE;
            m_method = "PUT";
            return sendRequest();
        }

        Observable &Url::patch(QByteArray body)
        {
            m_body = body;
            m_method = "PATCH";
            return sendRequest();
        }

        Observable &Url::patch(QJsonObject body)
        {
            return patch(QJsonDocument(body).toJson());
        }

        Observable &Url::patch(Form body)
        {
            QUrlQuery query;

            for (auto it = body.begin(); it != body.end(); ++it) {
                query.addQueryItem(it.key(), it.value());
            }
            return patch(query.query(QUrl::FullyEncoded).toUtf8());
        }

        Observable &Url::patch(QHttpMultiPart *multiPart)
        {
            m_multiPart = multiPart;
            m_bodyType = MULTIPART;
            m_method = "PATCH";
            return sendRequest();
        }

        Observable &Url::patch(QIODevice *device)
        {
            m_device = device;
            m_bodyType = DEVICE;
            m_method = "PATCH";
            return sendRequest();
        }

        Observable &Url::remove()
        {
            m_method = "DELETE";
            return sendRequest();
        }

        Observable &Url::options()
        {
            m_method = "OPTIONS";
            return sendRequest();
        }

        Url *Url::headers(const Headers &headers)
        {
            for (auto it = headers.begin(); it != headers.end(); ++it) {
                m_headers[it.key()] = it.value();
            }
            return this;
        }

        Url *Url::params(const Params &params)
        {
            m_params = params;
            return this;
        }

        void Url::addHeader(const QString &key, const QString &value)
        {
            m_headers[key] = value;
        }

        void Url::removeHeader(const QString &key)
        {
            m_headers.remove(key);
        }

        Observable &Url::sendRequest()
        {
            m_url.setQuery(makeQuery());

            QNetworkRequest request = QNetworkRequest(m_url);

            for (auto it = m_headers.begin(); it != m_headers.end(); ++it) {
                request.setRawHeader(it.key().toLatin1(), it.value().toLatin1());
            }

            QNetworkReply *reply;
            if (m_method == "HEAD") {
                reply = m_manager->head(request);
            } /*else if (m_method == "GET") {
                reply = m_manager->get(request);
            } else if (m_method == "POST") {
                reply = m_manager->post(request, nullptr);
            } else if (m_method == "PUT") {
                reply = m_manager->put(request, nullptr);
            } else if (m_method == "DELETE") {
                reply = m_manager->deleteResource(request);
            } */else {
                switch (m_bodyType) {
                case MULTIPART:
                    reply = m_manager->sendCustomRequest(request, m_method.toLatin1(), m_multiPart);
                    break;
                case DEVICE:
                    reply = m_manager->sendCustomRequest(request, m_method.toLatin1(), m_device);
                case DEFAULT:
                default:
                    reply = m_manager->sendCustomRequest(request, m_method.toLatin1(), m_body);
                    break;
                }
            }
            auto observable = new Observable(reply);
            connect(reply, SIGNAL(finished()), observable, SLOT(onResponse()));

            qInfo() << "HTTP: Request " << m_method << " " << m_url;

            return (*observable).map(
                [&](Response response)-> Response {
                    qInfo() << "HTTP: Response " << m_method << " " << m_url;
                    qInfo().noquote() << response;
                    return response;
                },
                [&](Response response)-> Response {
                    qInfo() << "HTTP: Error " << m_method << " " << m_url;
                    qInfo().noquote() << response;
                    return response;
                }
            );
        }

        QUrlQuery Url::makeQuery() const
        {
            QUrlQuery query;

            for (auto it = m_params.begin(); it != m_params.end(); ++it) {
                query.addQueryItem(it.key(), it.value());
            }
            return query;
        }
    }
}
