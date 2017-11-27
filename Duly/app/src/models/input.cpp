#include <QVector2D>
#include "models/input.h"

namespace duly_gui {
    namespace models {
        Input::Input(QString const &uid, QString const &name, QString const &description,
                     QString const &type, bool internal, QString const &linked_uid,
                     QObject *parent)
            : Variable(uid, name, description, QVector2D(), type, internal, parent), Identity(linked_uid)
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

        IClone *Input::clone() const
        {
            return new Input(uid(), name(), description(), type(), internal(), linked_uid());
        }
    }
}
