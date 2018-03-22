#ifndef HTTP_URL_H
#define HTTP_URL_H

#include <QUrl>
#include <QNetworkAccessManager>
#include "observable.h"
#include "types.h"

namespace dnai {
    namespace  http {
        enum BodyType {
            DEFAULT = 0,
            MULTIPART,
            DEVICE
        };
        class Url: public QObject
        {
            Q_OBJECT
        public:
            Url(QNetworkAccessManager *, QUrl const &);

        private:
            QNetworkAccessManager *m_manager;

            QUrl m_url;
            QString m_method;

            QMap<QString, QString> m_headers;
            QMap<QString, QString> m_params;

            BodyType m_bodyType;
            QByteArray m_body;
            QHttpMultiPart *m_multiPart;
            QIODevice *m_device;

        public:
            Observable &head();

            Observable &get();

            Observable &post(QByteArray);
            Observable &post(QJsonObject);
            Observable &post(Form);
            Observable &post(QHttpMultiPart *);
            Observable &post(QIODevice *);

            Observable &put(QByteArray);
            Observable &put(QJsonObject);
            Observable &put(Form);
            Observable &put(QHttpMultiPart *);
            Observable &put(QIODevice *);

            Observable &patch(QByteArray);
            Observable &patch(QJsonObject);
            Observable &patch(Form);
            Observable &patch(QHttpMultiPart *);
            Observable &patch(QIODevice *);

            Observable &remove();
            Observable &options();

        public:
            Url *headers(const Headers &);
            Url *params(const Params &);

        public:
            void addHeader(QString const &, QString const &);
            void removeHeader(QString const &);

        private:
            Observable &sendRequest();
            QUrlQuery makeQuery() const;
        };
    }
}

#endif // HTTP_URL_H
