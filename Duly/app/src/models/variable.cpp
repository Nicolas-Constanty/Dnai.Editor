#include "models/variable.h"
#include "include/controllers/clientcontroller.h"

namespace duly_gui {
    namespace models {
        Variable::Variable(QString const &uid, QString const &name, QString const &description, QVector2D const &position,
                           QString const &type, bool internal, int index, int listindex,
                           QObject *parent)
            : Common(uid, name, description, index, listindex, parent), Position(position), m_type(type), m_internal(internal)
        {
            m_type = ModelTypes::Variable;
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
            Position::serialize(obj);
            obj["type"] = m_type;
            obj["internal"] = m_internal;
        }

        void Variable::declare() const
        {
            ClientController::shared().sendDeclareEvent(PackageDataCom::ENTITYCORE::VARIABLE, 0, name(), PackageDataCom::VISIBILITYCORE::PUBLIC);
        }

        IClone *Variable::clone() const
        {
            return new Variable(uid(), name(), description(), position(), type(), internal(), index(), listIndex());
        }
    }
}
