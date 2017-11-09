#ifndef MODEL_COMMON_H
#define MODEL_COMMON_H

#include <QString>
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Common: virtual public IModel
        {
        public:
            Common(QString const &, QString const &);
            virtual ~Common();

            QString name() const;
            void setName(const QString &name);

            QString description() const;
            void setDescription(const QString &description);

        private:
            QString m_name;
            QString m_description;

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_COMMON_H
