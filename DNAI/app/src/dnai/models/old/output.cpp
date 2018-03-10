#include <QVector2D>
#include "dnai/models/output.h"

namespace dnai {
    namespace models {
		QList<QString> Output::m_editableProperties = {};
        Output::Output(const qint32 uid, QString const &name, QString const &description,
                       QString const &type, bool internal, QString const &linked_uid,
                       QObject *parent)
              : Variable(uid, name, description, QVector2D(), type, internal, 0, 0, parent), Identity(linked_uid)
        {

        }

        void Output::serialize(QJsonObject &obj) const
        {
            Variable::serialize(obj);
            Identity::serialize(obj);
        }

        void Output::declare() const
        {

        }

	    const QList<QString>& Output::editableProperties()
	    {
			if (m_editableProperties.empty())
				m_editableProperties += Variable::m_editableProperties + Identity::m_editableProperties;
			return m_editableProperties;
	    }

	    IClone *Output::clone() const
        {
            return new Output(uid(), name(), description(), varType(), internal(), linked_uid());
        }
    }
}
