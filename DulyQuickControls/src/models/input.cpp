#include "models/input.h"

namespace duly_gui {
    namespace models {
        Input::Input(QString const &name, QString const &description, QString const &type, bool internal,
                     QString const &uid, QString const &linked_uid)
            : Variable(name, description, type, internal), Identity(uid, linked_uid)
        {

        }

        Input::~Input()
        {

        }

        void Input::serialize(QJsonObject &obj) const
        {
            Variable::serialize(obj);
            Identity::serialize(obj);
        }
    }
}
