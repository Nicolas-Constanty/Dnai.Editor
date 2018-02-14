#ifndef HTTP_OBSERVABLE_H
#define HTTP_OBSERVABLE_H

#include <QNetworkReply>
#include <QStack>
#include "response.h"

namespace dnai {
    namespace  http {
        typedef std::function<Response (Response)> ResponseFunction;
        typedef std::function<Response (Response)> ErrorFunction;
        typedef std::function<void ()> FinalityFunction;

        class Observable: public QObject
        {
            Q_OBJECT
        public:
            Observable(QNetworkReply *);

        public slots:
            void onResponse();

        private:
            QNetworkReply *m_reply;
            QStack<ResponseFunction> m_responseHandlers;
            QStack<ErrorFunction> m_errorHandlers;
            QStack<FinalityFunction> m_finalityHandlers;

        public:
            Observable &map(ResponseFunction = nullptr, ErrorFunction = nullptr);
            void subscribe(ResponseFunction = nullptr, ErrorFunction = nullptr, FinalityFunction = nullptr);

        private:
            void callReponseHandlers(Response);
            void callErrorHandlers(Response);
            void callFinalityHandlers();
        };
    }
}

#endif // HTTP_OBSERVABLE_H
