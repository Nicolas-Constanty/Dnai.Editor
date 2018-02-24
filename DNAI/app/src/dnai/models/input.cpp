#include <QVector2D>
#include "dnai/models/input.h"

namespace dnai {
    namespace models {
		QList<QString> Input::m_editableProperties = {};
        Input::Input(const qint32 uid, QString const &name, QString const &description,
                     QString const &type, bool internal, QString const &linked_uid,
                     QObject *parent)
            : Variable(uid, name, description, QVector2D(), type, internal, 0, 0, parent), Identity(linked_uid)
        {

        }

        void Input::serialize(QJsonObject &obj) const
        {
            Variable::serialize(obj);
            Identity::serialize(obj);
        }

        void Input::declare() const
        {

        }

	    const QList<QString>& Input::editableProperties()
	    {
			if (m_editableProperties.empty())
				m_editableProperties += Variable::m_editableProperties + Identity::m_editableProperties;
			return m_editableProperties;
	    }

	    IClone *Input::clone() const
        {
            return new Input(uid(), name(), description(), varType(), internal(), linked_uid());
        }
    }
}
