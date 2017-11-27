#include "models/identity.h"

namespace duly_gui {
    namespace models {
        Identity::Identity(QString const &linked_uid)
            : m_linked_uid(linked_uid)
        {

        }

        Identity::~Identity()
        {

        }

        QString Identity::linked_uid() const
        {
            return m_linked_uid;
        }

        void Identity::setLinked_uid(const QString &linked_uid)
        {
            m_linked_uid = linked_uid;
        }

        void Identity::serialize(QJsonObject &obj) const
        {
            obj["linked_uid"] = m_linked_uid;
        }

        IClone *Identity::clone() const
        {
            return new Identity(linked_uid());
        }
    }
}
