#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "dnai/models/user.h"

namespace dnai {
class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(dnai::models::User *user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(void errors NOTIFY apiErrors CONSTANT)

public:
	explicit Session(QObject * parent = nullptr);

public:
    Q_INVOKABLE void signin(const QString &, const QString &);
    Q_INVOKABLE void getCurrentUser();
    Q_INVOKABLE bool uploadFile(const QString &);
    Q_INVOKABLE void updateCurentUserFiles();
    Q_INVOKABLE void logout();

signals:
    void userChanged(models::User *user);
	void apiErrors();

public:
    models::User *user() const;
    void setUser(models::User *user);

private:
    models::User *m_user;

};
}

#endif // SESSION_H
