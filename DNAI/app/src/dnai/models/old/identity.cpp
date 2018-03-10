#include "dnai/models/identity.h"

namespace dnai {
    namespace models {
		const QList<QString> Identity::m_editableProperties = {};
        Identity::Identity(QString const &linked_uid)
            : m_linked_uid(linked_uid)
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

        void Identity::declare() const
        {

        }

	    const QList<QString>& Identity::editableProperties()
	    {
			return m_editableProperties;
	    }

	    IClone *Identity::clone() const
        {
            return new Identity(linked_uid());
        }
    }
}
