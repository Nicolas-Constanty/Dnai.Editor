#include "serverthread.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerThread serverThread;

    serverThread.start();

    return a.exec();
}
