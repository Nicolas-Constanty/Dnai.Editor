#include "mainwindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QSplitter>

#include "nodecanvas.h"
#include "qtroundedrectitem.h"
#include "MoveCommand.h"
#include "commandmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QWidget mainWidget;

    auto menuBar    = new QMenuBar();
    auto m = new QMenu("File");
    auto saveAction = m->addAction("Save..");
    auto loadAction = m->addAction("Load..");
    menuBar->addMenu(m);
    menuBar->setMaximumHeight(20);

    QVBoxLayout *l = new QVBoxLayout(&mainWidget);

    l->addWidget(menuBar);
    auto scene = new QGraphicsScene();
    QtRoundedRectItem *e = new QtRoundedRectItem(QRect(0,0,150*3,150), 15, 15);
    e->setFlags(QGraphicsItem::ItemIsMovable);
    scene->addItem(e);

    QWidget *Canvas = new QWidget;
    QHBoxLayout *container_layout = new QHBoxLayout;


    l->addWidget(Canvas);
    auto *splitter = new QSplitter;
    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(new NodeCanvas(scene));
    splitter->addWidget(new NodeCanvas(scene));

    container_layout->addWidget(splitter);
    Canvas->setLayout(container_layout);

    mainWidget.setWindowTitle("Duly");
    mainWidget.resize(800, 600);
    mainWidget.showNormal();
    auto c = new MoveCommand(e, QPoint(10, 10));
    auto cm = new CommandManager();
    cm->RegisterCommand(c);
    cm->ExecAll();
    qDebug() << "End";

    return a.exec();
}
