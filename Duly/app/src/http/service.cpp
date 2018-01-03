#include <QNetworkAccessManager>
#include "http/service.h"

namespace duly_gui {
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
    }
}
