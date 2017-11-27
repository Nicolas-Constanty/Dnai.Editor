#ifndef MODEL_VARIABLE_H
#define MODEL_VARIABLE_H

#include <QString>
#include <QVariant>
#include "models/common.h"
#include "models/position.h"
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Variable: public Common, public Position, virtual public IModel
        {
        public:
            Variable(QString const &, QString const &, QString const &, QVector2D const &, QString const &, bool, QObject *parent = nullptr);
            virtual ~Variable();

        private:
            QString m_type;
            bool m_internal;
//            QVariant value;

        public:
            QString type() const;
            void setType(const QString &type);

            bool internal() const;
            void setInternal(bool internal);


            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_VARIABLE_H
