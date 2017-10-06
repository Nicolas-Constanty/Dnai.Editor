QT += qml quick quickcontrols2

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QNANO_USE_RENDERNODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += baseio.cpp \
    beziercurve.cpp \
    commanddecorator.cpp \
    commandmanager.cpp \
    dulycanvas.cpp \
    genericnode.cpp \
    input.cpp \
    io.cpp \
    ioquickitem.cpp \
    line.cpp \
    link.cpp \
    main.cpp \
    output.cpp \
    roundedrectangle.cpp \
    debugdecorator.cpp \
    eventutilities.cpp \
    focusmanager.cpp \
    flow.cpp \
    baselinkable.cpp \
    customshape.cpp \
    moveCommand.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = QT_INSTALL_QML/QtQml/Models.2

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = QT_INSTALL_QML/QtQml.2/Models

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS +=

HEADERS += baseio.h \
    beziercurve.h \
    commanddecorator.h \
    commandmanager.h \
    debugdecorator.h \
    genericnode.h \
    icommand.h \
    ilinkable.h \
    input.h \
    io.h \
    ioquickitem.h \
    line.h \
    link.h \
    linkabletype.h \
    observablelist.h \
    output.h \
    resourcesnode.h \
    roundedrectangle.h \
    dulycanvas.h \
    eventutilities.h \
    focusmanager.h \
    flow.h \
    baselinkable.h \
    customshape.h \
    moveCommand.h
