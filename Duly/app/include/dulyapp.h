#ifndef DULYAPP_H
#define DULYAPP_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

namespace duly_gui {
    class DulyApp : public QGuiApplication
    {
    public:
        DulyApp(int & argc, char **argv);
        bool eventFilter(QObject *object, QEvent *event) override;
    };
}

#endif // DULYAPP_H
