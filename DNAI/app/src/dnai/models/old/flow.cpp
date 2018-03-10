#include "dnai/models/flow.h"

namespace dnai {
    namespace models {
		QList<QString> Flow::m_editableProperties = {};
        Flow::Flow(const qint32 uid, QString const &name, QString const &description, QString const &linked_uid, QObject *parent)
            :Common(uid, name, description, 0, 0, parent), Identity(linked_uid)
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

	    const QList<QString>& Flow::editableProperties()
	    {
			if (m_editableProperties.empty())
				m_editableProperties += Common::m_editableProperties + Identity::m_editableProperties;
			return m_editableProperties;
	    }

	    IClone *Flow::clone() const
        {
            return new Flow(uid(), name(), description(), linked_uid());
        }
    }
}
