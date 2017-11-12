#ifndef IMODEL_H
#define IMODEL_H

#include <QJsonObject>

namespace duly_gui {
    namespace models {
        class IModel
        {
        public:
            virtual ~IModel() {}
        public:
            virtual void serialize(QJsonObject &) const = 0;
        };
    }
}

#endif // IMODEL_H
