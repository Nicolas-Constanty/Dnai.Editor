#include "dnai/http/response.h"

namespace dnai {
namespace  http {
        Response::operator QString() const
        {
            auto obj = QJsonObject{
                {"status", QJsonObject{
                    {"code", this->status.code},
                    {"message", this->status.message},
                    }
                },
                {"body", this->body}
            };
            return QJsonDocument(obj).toJson(QJsonDocument::Indented);
        }
    }
}
