#ifndef HTTP_SERVICE_H
#define HTTP_SERVICE_H

#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QFile>
#include <sstream>
#include <iostream>
#include "url.h"
#include "config.h"

namespace dnai {
    namespace  http {
        class Service
        {
        public:
            static void Init(const Config &);
            static void callInterceptors(Url*);
            static void addInterceptor(InterceptorFunction);

            static QHttpPart makeHttpPart(QString const &, QString const &);
            static QHttpPart makeHttpPart(QString const &, QFile *);

        public:
            template<typename... Args>
            static Url *url(Args const&... args)
            {
                std::ostringstream oss;
                oss << Service::m_config.base_url;
                int a[] = {0, ((void)(oss << args << "/"), 0) ... };
                static_cast<void>(a);
                oss.str().pop_back();
                auto url = new Url(m_manager, QUrl(QString::fromStdString(oss.str())));
                Service::callInterceptors(url);
                return url;
            }

        private:
            static QNetworkAccessManager *m_manager;
            static Config m_config;
        };
    }
}

#endif // HTTP_SERVICE_H
