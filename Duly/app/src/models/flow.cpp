#include "models/flow.h"

namespace duly_gui {
    namespace models {
        Flow::Flow(QString const &uid, QString const &name, QString const &description, QString const &linked_uid, QObject *parent)
            :Common(uid, name, description, 0, 0, parent), Identity(linked_uid)
        {

        }

        Flow::~Flow()
        {

        }

        void Flow::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            Identity::serialize(obj);
        }

        void Flow::declare() const
        {

        }

        IClone *Flow::clone() const
        {
            return new Flow(uid(), name(), description(), linked_uid());
        }
    }
}
