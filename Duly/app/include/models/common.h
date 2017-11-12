#ifndef MODEL_COMMON_H
#define MODEL_COMMON_H

#include <QObject>
#include <QString>
#include "models/imodel.h"

namespace duly_gui {
    namespace models {
        class Common: public QObject, virtual public IModel
        {
            Q_OBJECT
            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

        public:
            Common(QString const &, QString const &, QObject * = nullptr);
            virtual ~Common();

            QString name() const;
            void setName(const QString &name);

            QString description() const;
            void setDescription(const QString &description);

        private:
            QString m_name;
            QString m_description;

        signals:
            void nameChanged();
            void descriptionChanged();

            // IModel interface
        public:
            virtual void serialize(QJsonObject &) const;
        };
    }
}

#endif // MODEL_COMMON_H
