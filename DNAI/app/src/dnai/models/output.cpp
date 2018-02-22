#include <QVector2D>
#include "dnai/models/output.h"

namespace dnai {
    namespace models {
        Output::Output(const qint32 uid, QString const &name, QString const &description,
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
            return new Output(uid(), name(), description(), varType(), internal(), linked_uid());
        }
    }
}
