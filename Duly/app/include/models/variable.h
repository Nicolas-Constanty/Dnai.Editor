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
            Variable(const QString &uid, const QString &name, const QString &description, const QVector2D &position, const QString &type, bool internal, int index, int listindex, QObject *parent= nullptr);
            virtual ~Variable();

        private:
            QString m_vartype;
            bool m_internal;
//            QVariant value;

        public:
            QString varType() const;
            void setVarType(const QString &type);

            bool internal() const;
            void setInternal(bool internal);


            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
            virtual void declare() const;

            // IClone interface
        private:
            IClone *clone() const;
        };
    }
}

#endif // MODEL_VARIABLE_H
