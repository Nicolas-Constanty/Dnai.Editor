#ifndef MODEL_IDENTITY_H
#define MODEL_IDENTITY_H

#include <QString>
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Identity: virtual public IModel
        {
        public:
            Identity(QString const &);
            virtual ~Identity();

            QString linked_uid() const;
            void setLinked_uid(const QString &linked_uid);

        private:
            QString m_linked_uid;

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

#endif // MODEL_IDENTITY_H
