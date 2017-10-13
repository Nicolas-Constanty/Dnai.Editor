QT += qml quick quickcontrols2

CONFIG += c++14

INCLUDEPATH += include/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QNANO_USE_RENDERNODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/baseio.cpp \
    src/beziercurve.cpp \
    src/dulycanvas.cpp \
    src/genericnode.cpp \
    src/input.cpp \
    src/io.cpp \
    src/ioquickitem.cpp \
    src/line.cpp \
    src/link.cpp \
    src/main.cpp \
    src/output.cpp \
    src/roundedrectangle.cpp \
    src/eventutilities.cpp \
    src/focusmanager.cpp \
    src/flow.cpp \
    src/baselinkable.cpp \
    src/customshape.cpp \
    src/linkablebezieritem.cpp \
    src/scalableitem.cpp \
    src/dulyscene.cpp

SOURCES += src/commands/moveCommand.cpp \
    src/commands/commanddecorator.cpp \
    src/commands/commandmanager.cpp \
    src/commands/debugdecorator.cpp \

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

HEADERS += include/baseio.h \
    include/beziercurve.h \
    include/genericnode.h \
    include/ilinkable.h \
    include/input.h \
    include/io.h \
    include/ioquickitem.h \
    include/line.h \
    include/link.h \
    include/linkabletype.h \
    include/observablelist.h \
    include/output.h \
    include/resourcesnode.h \
    include/roundedrectangle.h \
    include/dulycanvas.h \
    include/eventutilities.h \
    include/focusmanager.h \
    include/flow.h \
    include/baselinkable.h \
    include/customshape.h \
    include/linkablebezieritem.h \
    include/scalableitem.h \
    include/dulyscene.h \
    include/iscalable.h

HEADERS += include/commands/commanddecorator.h \
    include/commands/commandmanager.h \
    include/commands/debugdecorator.h \
    include/commands/icommand.h \
    include/commands/moveCommand.h \

