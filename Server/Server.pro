QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += include/

TEMPLATE = app

SOURCES += src/main.cpp \
    src/dulyserver.cpp \
    src/dulycommunicationserver.cpp \
    src/packagemanager.cpp \
    src/eventmanager.cpp \
    src/createpackagefunction.cpp \
    src/server.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += SERVER_MODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    include/dulyserver.h \
    include/dulycommunicationserver.h \
    include/packagemanager.h \
    include/headercommunication.h \
    include/authentificationpackage.h \
    include/eventregisterpackage.h \
    include/eventsendpackage.h \
    include/eventmanager.h \
    include/server.h
