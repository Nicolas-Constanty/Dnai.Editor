#include "models/common.h"

namespace duly_gui {
    namespace models {
        Common::Common(QString const &uid, QString const &name, QString const &description, QObject *parent)
            : QObject(parent), m_uid(uid), m_name(name), m_description(description)
        {

        }

        Common::~Common()
        {

        }

        QString Common::uid() const
        {
            return m_uid;
        }

        void Common::setUid(const QString &uid)
        {
            m_uid = uid;
        }
        
        QString Common::name() const
        {
            return m_name;
        }
        
        void Common::setName(const QString &name)
        {
            m_name = name;
        }
        
        QString Common::description() const
        {
            return m_description;
        }
        
        void Common::setDescription(const QString &description)
        {
            m_description = description;
        }

        void Common::serialize(QJsonObject &obj) const
        {
            obj["uid"] = m_uid;
            obj["name"] = m_name;
            obj["description"] = m_description;
        }

        IClone *Common::clone() const
        {
            return new Common(uid(), name(), description());
        }
    }
}
