#include "models/flow.h"

namespace duly_gui {
    namespace models {
        Flow::Flow(QString const &uid, QString const &linked_uid)
            :Identity(uid, linked_uid)
        {

        }

        Flow::~Flow()
        {

        }

        void Flow::serialize(QJsonObject &obj) const
        {
            Identity::serialize(obj);
        }
    }
}
