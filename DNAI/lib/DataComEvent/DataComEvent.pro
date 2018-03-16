QT += core
QT -= gui

CONFIG += c++14

TARGET = DataComEvent
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG += warn_off
DESTDIR = $$PWD/../

TEMPLATE = lib

INCLUDEPATH += $${PWD}/../Cerealization/repository/include

#main.cpp \

SOURCES += \
    datacomeventfactory.cpp \
    coreserialoperations.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Shared_include/datacomeventfactory.h \
    Shared_include/packagecore.h \
    Shared_include/coreserialoperations.h \
    Shared_include/commands/commands.h \
    Shared_include/commands/declarator/declare.h \
    Shared_include/replies/replies.h \
    Shared_include/replies/declared.h

#CONFIG(release, debug|release) {
#unix:LIBS += -L$${PWD}/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/Library/ -llibprotobuf
#}
#CONFIG(debug, debug|release) {
#unix:LIBS += -L$${PWD}/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/Library/ -llibprotobufd
#}
#/usr/local/include/ \

INCLUDEPATH += ./Shared_include/
