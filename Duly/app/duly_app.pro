QT += qml quickcontrols2

CONFIG += c++14
CONFIG += object_parallel_to_source

INCLUDEPATH += include/


CONFIG(release, debug|release) {
win32:RC_FILE = duly.rc
unix:ICON = DNAI_icon.icns
}
#RC_FILE = duly.rc

#ICON = DNAI_icon.icns

settingsfolder.path = $${OUT_PWD}/settings
settingsfolder.files = settings/*

settingsfolderconf.path = $${OUT_PWD}/settings/conf
settingsfolderconf.files = settings/conf/*/*

INSTALLS += settingsfolder
INSTALLS += settingsfolderconf

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QNANO_USE_RENDERNODE
DEFINES += QPM_INIT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CORE
SOURCES += src/baseio.cpp \
    src/link.cpp \
    src/main.cpp \
    src/eventutilities.cpp \
    src/focusmanager.cpp \
    src/baselinkable.cpp \
    src/dulyscene.cpp \
    src/dulyapp.cpp \
    src/commands/movecommand.cpp \
    src/commands/movenodecommand.cpp \
    src/commands/movecanvascommand.cpp \
    src/commands/zoomcanvascommand.cpp \
    src/manager.cpp \
    src/project.cpp \
    src/views/context.cpp \
    src/views/class.cpp \
    src/models/list/listmodelcontext.cpp \
    src/dulysettings.cpp \
    src/dulysettingsmodel.cpp \
    src/views/declarationview.cpp \
    src/views/declarationcanvas.cpp \
    src/controllers/clientcontroller.cpp \
    src/processmanager.cpp \
    src/models/treemodel.cpp \
    src/models/treeitem.cpp \
    src/models/namespacebarmodel.cpp \
    src/models/namespacebaritem.cpp \
    layouthandler.cpp

#VIEWS
SOURCES += src/views/beziercurve.cpp \
    src/views/customshape.cpp \
    src/views/dulycanvas.cpp \
    src/views/flow.cpp \
    src/views/genericnode.cpp \
    src/views/input.cpp \
    src/views/io.cpp \
    src/views/line.cpp \
    src/views/linkablebezieritem.cpp \
    src/views/output.cpp \
    src/views/roundedrectangle.cpp \
    src/views/console.cpp \


#COMMANDS
SOURCES += \
    src/commands/commanddecorator.cpp \
    src/commands/commandmanager.cpp \
    src/commands/debugdecorator.cpp \
    src/commands/command.cpp \


#CONTROLLERS
SOURCES += src/controllers/inputcontroller.cpp \
    src/controllers/outputcontroller.cpp \
    src/controllers/consolecontroller.cpp \

#MODELS
SOURCES += src/models/class.cpp \
    src/models/common.cpp \
    src/models/context.cpp \
    src/models/flow.cpp \
    src/models/function.cpp \
    src/models/identity.cpp \
    src/models/input.cpp \
    src/models/node.cpp \
    src/models/output.cpp \
    src/models/variable.cpp \
    src/models/position.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS +=

#CORE
HEADERS += include/baseio.h \
    include/baselinkable.h \
    include/dulyscene.h \
    include/eventutilities.h \
    include/focusmanager.h \
    include/ilinkable.h \
    include/link.h \
    include/linkabletype.h \
    include/dulyapp.h \
    include/commands/movenodecommand.h \
    include/commands/movecommand.h \
    include/testconnection.h \
    include/manager.h \
    include/project.h \
    include/views/context.h \
    include/views/class.h \
    include/views.h \
    include/dulysettings.h \
    include/dulysettingsmodel.h \
    include/views/declarationview.h \
    include/views/declarationcanvas.h \
    include/controllers/clientcontroller.h \
    include/iotype.h \
    include/flowtype.h \
    include/processmanager.h \
    include/declarationtype.h \
    include/models/treemodel.h \
    include/models/treeitem.h \
    include/models/treeitem.h \
    include/models/namespacebarmodel.h \
    include/models/namespacebaritem.h \
    layouthandler.h

#VIEWS
HEADERS += include/views/beziercurve.h \
    include/views/customshape.h \
    include/views/dulycanvas.h \
    include/views/flow.h \
    include/views/genericnode.h \
    include/views/input.h \
    include/views/io.h \
    include/views/iscalable.h \
    include/views/line.h \
    include/views/linkablebezieritem.h \
    include/views/output.h \
    include/views/roundedrectangle.h \
    include/views/console.h \

#COMMANDS
HEADERS += include/commands/commanddecorator.h \
    include/commands/commandmanager.h \
    include/commands/debugdecorator.h \
    include/commands/icommand.h \
    include/commands/command.h \


#CONTROLLERS
HEADERS += include/controllers/inputcontroller.h \
    include/controllers/outputcontroller.h \
    include/controllers/consolecontroller.h \

#MODELS
HEADERS += include/models/common.h \
    include/models/context.h \
    include/models/class.h \
    include/models/node.h \
    include/models/variable.h \
    include/models/input.h \
    include/models/output.h \
    include/models/flow.h \
    include/models/function.h \
    include/models/identity.h \
    include/models/imodel.h \
    include/models/iclone.h \
    include/models/position.h \
    include/models/list/listmodelcontext.h

#LIB
DEPENDPATH += $${PWD}/../lib/event_client/
INCLUDEPATH += $${PWD}/../lib/event_client/

INCLUDEPATH += $${PWD}/../lib/DataComEvent/Shared_include/

#begin library network
LIBS += -L$${PWD}/../lib/ -lEventClient -lDataComEvent

#CONFIG(release, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobuf
#}
#CONFIG(debug, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobufd
#}

#end library Data Event
