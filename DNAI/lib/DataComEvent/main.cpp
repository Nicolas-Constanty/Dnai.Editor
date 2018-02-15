#include <QCoreApplication>
#include "core.pb.h"
#include <QDebug>
#include <QString>
/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    Declare declare;
    char array[4096];

    declare.set_entitytype(::ENTITY::CONTEXT);
    declare.set_containerid(3);
    declare.set_name("YOLO");
    declare.set_visibility(PRIVATE);


    if (declare.SerializeToArray(array, sizeof(array))) {
        Declare secondDeclare;
        secondDeclare.ParseFromArray(array, sizeof(array));
        qDebug() << QString(secondDeclare.name().c_str());
    } else {
        qDebug() << "FAILED";
    }

    return a.exec();
}
*/
