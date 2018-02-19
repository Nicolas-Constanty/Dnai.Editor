#include <QNetworkAccessManager>
#include "dnai/http/service.h"

namespace dnai {
    namespace  http {
    QNetworkAccessManager* Service::m_manager = new QNetworkAccessManager();
    Config Service::m_config = Config{};

        void Service::Init(const Config &config)
        {
            m_config = config;
            if (m_config.base_url.back() != '/') {
                m_config.base_url.push_back('/');
            }
        }

        void Service::callInterceptors(Url *url)
        {
            foreach (auto func, m_config.interceptors) {
                func(url);
            }
        }

        void Service::addInterceptor(InterceptorFunction interceptor)
        {
            m_config.interceptors.push_back(interceptor);
        }

        QHttpPart Service::makeHttpPart(const QString &key, const QString &value)
        {
            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
            part.setBody(value.toUtf8());
            return part;
        }

        QHttpPart Service::makeHttpPart(const QString &key, QFile *file)
        {
            file->open(QIODevice::ReadOnly);

            QHttpPart part;
            part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
            part.setBody(file);
            return part;
        }
    }
}
