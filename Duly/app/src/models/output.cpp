#include "models/output.h"

namespace duly_gui {
    namespace models {
        Output::Output(QString const &name, QString const &description, QString const &type, bool internal,
                       QString const &uid, QString const &linked_uid)
              : Variable(name, description, type, internal), Identity(uid, linked_uid)
        {

        }

        Output::~Output()
        {

        }

        void Output::serialize(QJsonObject &obj) const
        {
            Variable::serialize(obj);
            Identity::serialize(obj);
        }
    }
}
