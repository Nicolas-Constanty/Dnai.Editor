#include <QJsonDocument>
#include "dnai/http/observable.h"

namespace dnai {
    namespace  http {
        Observable::Observable(QNetworkReply *reply): QObject (nullptr), m_reply(reply)
        {

        }

        void Observable::onResponse()
        {
            Response response;
            response.status = {
                m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                m_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toByteArray()
            };

            response.body = QJsonDocument::fromJson(m_reply->readAll()).object();

            switch (m_reply->error()) {
            case QNetworkReply::NetworkError::NoError:
                callReponseHandlers(response);
                break;
            default:
                callErrorHandlers(response);
                break;
            }
            callFinalityHandlers();
            m_reply->deleteLater();
        }

        Observable &Observable::map(ResponseFunction response, ErrorFunction error)
        {
            if (response) {
                m_responseHandlers.push(response);
            }
            if (error) {
                m_errorHandlers.push(error);
            }
            return *this;
        }

        void Observable::subscribe(ResponseFunction response, ErrorFunction error, FinalityFunction finality)
        {
            if (response) {
                m_responseHandlers.push(response);
            }
            if (error) {
                m_errorHandlers.push(error);
            }
            if (finality) {
                m_finalityHandlers.push(finality);
            }
        }

        void Observable::callReponseHandlers(Response response)
        {
            foreach (auto func, m_responseHandlers) {
                response = func(response);
            }
        }

        void Observable::callErrorHandlers(Response response)
        {
            foreach (auto func, m_errorHandlers) {
                response = func(response);
            }
        }

        void Observable::callFinalityHandlers()
        {
            foreach (auto func, m_finalityHandlers) {
                func();
            }
        }
    }
}
