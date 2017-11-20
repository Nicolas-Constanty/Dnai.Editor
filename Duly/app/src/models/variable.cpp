#include "models/variable.h"

namespace duly_gui {
    namespace models {
        Variable::Variable(QString const &name, QString const &description, QString const &type, bool internal)
            : Common(name, description), m_type(type), m_internal(internal)
        {

        }

        Variable::~Variable()
        {

        }

        QString Variable::type() const
        {
            return m_type;
        }
        
        void Variable::setType(const QString &type)
        {
            m_type = type;
        }
        
        bool Variable::internal() const
        {
            return m_internal;
        }
        
        void Variable::setInternal(bool internal)
        {
            m_internal = internal;
        }

        void Variable::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            obj["type"] = m_type;
            obj["internal"] = m_internal;
        }

        IClone *Variable::clone() const
        {
            return new Variable(name(), description(), type(), internal());
        }
    }
}
