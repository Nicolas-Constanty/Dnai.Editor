#ifndef TOASTERMANAGERSERVICE_H
#define TOASTERMANAGERSERVICE_H

#include <QQmlEngine>
#include <QObject>

class ToasterManagerService : public QObject {
    Q_OBJECT

public:
    ToasterManagerService() = default;
    ToasterManagerService(ToasterManagerService const&) = delete;             // Copy construct
    ToasterManagerService(ToasterManagerService&&) = delete;                  // Move construct
    ToasterManagerService& operator=(ToasterManagerService const&) = delete;  // Copy assign
    ToasterManagerService& operator=(ToasterManagerService &&) = delete;      // Move assign

public:
    Q_INVOKABLE void notifyInformation(QString const &text);

private:
    QQmlEngine *m_engine;
};

#endif // TOASTERMANAGERSERVICE_H
