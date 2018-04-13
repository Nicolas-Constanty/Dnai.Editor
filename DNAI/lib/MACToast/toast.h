#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QString>

class Q_DECL_EXPORT ToastMac
{
public:
    ToastMac();

    void show(QString const &title, QString const &info);
};

#endif // TOAST_H
