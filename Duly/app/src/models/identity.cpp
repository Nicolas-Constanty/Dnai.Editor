#include "models/identity.h"

namespace duly_gui {
    namespace models {
        Identity::Identity(QString const &uid, QString const &linked_uid)
            : m_uid(uid), m_linked_uid(linked_uid)
        {

        }

        Identity::~Identity()
        {

        }

        QString Identity::uid() const
        {
            return m_uid;
        }

        void Identity::setUid(const QString &uid)
        {
            m_uid = uid;
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
            obj["uid"] = m_uid;
            obj["linked_uid"] = m_linked_uid;
        }

        IClone *Identity::clone() const
        {
            return new Identity(uid(), linked_uid());
        }
    }
}
