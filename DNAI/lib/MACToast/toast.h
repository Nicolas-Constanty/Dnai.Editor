#ifndef TOAST_H
#define TOAST_H

#include <QObject>
#include <QString>

class Q_DECL_EXPORT Toast
{
public:
    Toast();

    void show(QString const &title, QString const &info);
};

#endif // TOAST_H
