#ifndef TOASTERMANAGERSERVICE_H
#define TOASTERMANAGERSERVICE_H

#include <QList>
#include <QQuickItem>
#include <QQmlEngine>
#include <QObject>
#include "dnai/views/toast.h"

class ToasterManagerService : public QObject {
    Q_OBJECT

public:
    ToasterManagerService() = default;
    ToasterManagerService(ToasterManagerService const&) = delete;             // Copy construct
    ToasterManagerService(ToasterManagerService&&) = delete;                  // Move construct
    ToasterManagerService& operator=(ToasterManagerService const&) = delete;  // Copy assign
    ToasterManagerService& operator=(ToasterManagerService &&) = delete;      // Move assign

private:
    int getYposition(int absIdx = -1) const;

public:
    void timeout(Toast *toast);

public slots:
    void removeOne(Toast *toast);

private:
    Toast *createToast(QString const &text, std::function<void ()> func);

public:
    Q_INVOKABLE void notifyInformation(QString const &text, std::function<void ()> func);
    Q_INVOKABLE void notifyError(QString const &text, std::function<void ()> func);
    Q_INVOKABLE void notifyWarning(QString const &text, std::function<void ()> func);
    Q_INVOKABLE void notifySuccess(QString const &text, std::function<void ()> func);

private:
    QQmlEngine *m_engine;
    QList<Toast *> m_list;
};

#endif // TOASTERMANAGERSERVICE_H
