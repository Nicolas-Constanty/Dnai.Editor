#include <QVector2D>
#include "models/output.h"

namespace duly_gui {
    namespace models {
        Output::Output(QString const &uid, QString const &name, QString const &description,
                       QString const &type, bool internal, QString const &linked_uid,
                       QObject *parent)
              : Variable(uid, name, description, QVector2D(), type, internal, 0, 0, parent), Identity(linked_uid)
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

        void Output::declare() const
        {

        }

        IClone *Output::clone() const
        {
            return new Output(uid(), name(), description(), type(), internal(), linked_uid());
        }
    }
}
