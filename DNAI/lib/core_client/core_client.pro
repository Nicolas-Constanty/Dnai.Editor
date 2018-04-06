#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T18:27:43
#
#-------------------------------------------------

QT       -= gui
QT      += network

TARGET = CoreClient
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
DESTDIR = $$PWD/../

TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    $${PWD}/../Cerealization/repository/include/ \
    $${PWD}/../event_client/include/ \
    $${PWD}/include/

LIBS += -lEventClient -lCerealization

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/serialoperations.cpp \
    src/core.cpp \
    src/client.cpp

HEADERS += \
    include/core.h \
    include/serialoperations.h \
    include/client.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
