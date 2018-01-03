#include "http/response.h"

namespace duly_gui {
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
