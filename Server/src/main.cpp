#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qint16 port = 0;
    QString keySem;

    int i = 1;
    while (argv[i] && argv[i + 1]) {
        QString mode(argv[i]);
        if (mode == "-p") {
            QString portStr(argv[i + 1]);
            port = (qint16)portStr.toInt();
        } else if (mode == "-S") {
            keySem = QString(argv[i + 1]);
        }
        ++i;
    }
    Server server(false, port, keySem);

    server.start();

    return a.exec();
}
