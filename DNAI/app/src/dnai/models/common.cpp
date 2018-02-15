#include "dnai/models/common.h"

namespace dnai {
    namespace models {
        Common::Common(QString const &uid, QString const &name, QString const &description, int index, int listindex, QObject *parent)
            : QObject(parent), m_uid(uid), m_name(name), m_description(description), m_index(index), m_listindex(listindex), m_select(false), m_type(ModelTypes::Common)
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

        void Common::setIndex(int i)
        {
            if (i == m_index)
                return;
            m_index = i;
            emit indexChanged(i);
        }

        void Common::setListIndex(int i)
        {
            if (i == m_index)
                return;
            m_listindex = i;
            emit listIndexChanged(i);
        }

        void Common::setType(int t)
        {
            if (t == m_type)
                return;
            m_type = t;
            emit typeChanged(t);
        }

        void Common::select(bool s)
        {
            m_select = s;
        }

        void Common::serialize(QJsonObject &obj) const
        {
            obj["uid"] = m_uid;
            obj["name"] = m_name;
            obj["description"] = m_description;
        }

        void Common::declare() const
        {

        }

        IClone *Common::clone() const
        {
            return new Common(uid(), name(), description(), index(), listIndex());
        }
    }
}
