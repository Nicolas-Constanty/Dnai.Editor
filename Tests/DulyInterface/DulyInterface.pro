#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T15:07:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DulyInterface
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    node.cpp \
    border.cpp \
    nodecanvas.cpp \
    qtroundedrectitem.cpp \
    MoveCommand.cpp \
    commandmanager.cpp \
    commanddecorator.cpp \
    debugdecorator.cpp \
    anode.cpp \
    ainput.cpp \
    nodemanager.cpp \
    linewidget.cpp \
    graphicsline.cpp

HEADERS += \
        mainwindow.h \
    node.h \
    border.h \
    nodecanvas.h \
    qtroundedrectitem.h \
    icommand.h \
    MoveCommand.h \
    commandmanager.h \
    commanddecorator.h \
    iclonable.h \
    debugdecorator.h \
    anode.h \
    ainput.h \
    nodemanager.h \
    linewidget.h \
    graphicsline.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    main.qrc
