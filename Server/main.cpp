#include "server.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;

    server.start();

    return a.exec();
}
