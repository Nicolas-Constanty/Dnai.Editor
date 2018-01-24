#ifndef MODEL_USER_H
#define MODEL_USER_H

#include <QObject>

namespace duly_gui {
    namespace models {
        class User: public QObject {
            Q_OBJECT

            Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
            Q_PROPERTY(QString profile_url READ profile_url WRITE setProfile_url NOTIFY profile_urlChanged)
        public:
            User();
            ~User();

            QString name() const;
            void setName(const QString &name);

            QString profile_url() const;
            void setProfile_url(const QString &profile_url);

        private:
            QString m_name;
            QString m_profile_url;

        signals:
            void nameChanged(QString &);
            void profile_urlChanged(QString &);
        };
    }
}

#endif // MODEL_USER_H
