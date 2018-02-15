#ifndef HTTP_URL_H
#define HTTP_URL_H

#include <QUrl>
#include <QNetworkAccessManager>
#include "observable.h"
#include "types.h"

namespace dnai {
    namespace  http {
        class Url: public QObject
        {
            Q_OBJECT
        public:
            Url(QNetworkAccessManager *, QUrl const &);

        private:
            QNetworkAccessManager *m_manager;
            QUrl m_url;
            QString m_method;
            QByteArray m_body;
            QMap<QString, QString> m_headers;
            QMap<QString, QString> m_params;

        public:
            Observable &head();
            Observable &get();
            Observable &post(QByteArray);
            Observable &post(QJsonObject);
            Observable &post(Form);
            Observable &put(QByteArray);
            Observable &put(QJsonObject);
            Observable &put(Form);
            Observable &patch(QByteArray);
            Observable &patch(QJsonObject);
            Observable &patch(Form);
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
