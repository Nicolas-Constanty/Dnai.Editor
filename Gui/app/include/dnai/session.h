#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "dnai/models/user.h"

namespace dnai {
class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(dnai::models::User *user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(bool rememberUser READ rememberUser WRITE setRememberUser NOTIFY rememberUserChanged)

public:
	explicit Session(QObject * parent = nullptr);

public:
    Q_INVOKABLE void signin(const QString &, const QString &);
    Q_INVOKABLE void getCurrentUser();
    Q_INVOKABLE bool uploadFile(const QString &);
    Q_INVOKABLE void updateCurentUserFiles();
    Q_INVOKABLE void logout();
    Q_INVOKABLE void downloadProjectData(uint, const QString &);

signals:
    void userChanged(models::User *user);
	void apiErrors();
    void rememberUserChanged(bool);

public:
    models::User *user() const;
    bool rememberUser() const;
    void setUser(models::User *user);
    void setRememberUser(bool);

private:
    models::User *m_user;
    bool m_rememberUser;
};
}

#endif // SESSION_H

