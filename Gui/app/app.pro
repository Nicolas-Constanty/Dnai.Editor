QT += qml quickcontrols2 network

CONFIG += c++14
CONFIG += object_parallel_to_source
CONFIG += resources_big
CONFIG += no_batch

INCLUDEPATH += include/
TARGET = DNAI
TEMPLATE = app

CONFIG(release, debug|release) {
win32:RC_FILE = dnai.rc
unix:ICON = DNAI_icon.icns
}


#INSTALLS += settingsfolderconf

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QNANO_USE_RENDERNODE
DEFINES += QPM_INIT

#Logiciel VERSION RELEASE
VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_BUILD = 21

DEFINES += "VERSION_MAJOR=$${VERSION_MAJOR}"\
       "VERSION_MINOR=$${VERSION_MINOR}"\
       "VERSION_BUILD=$${VERSION_BUILD}"

#Target version
VERSION = "$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}"

DEFINES += DNAI_VERSION_RELEASE=\\\"$${VERSION}\\\"
#END

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CORE
SOURCES += \
    src/dnai/api/api.cpp \
    src/dnai/commands/command.cpp \
    src/dnai/commands/commanddecorator.cpp \
    src/dnai/commands/commandmanager.cpp \
    src/dnai/commands/debugdecorator.cpp \
    src/dnai/commands/movecanvascommand.cpp \
    src/dnai/commands/movecommand.cpp \
    src/dnai/commands/movenodecommand.cpp \
    src/dnai/commands/zoomcanvascommand.cpp \
    src/dnai/controllers/consolecontroller.cpp \
    src/dnai/controllers/icontroller.cpp \
    src/dnai/controllers/inputcontroller.cpp \
    src/dnai/controllers/outputcontroller.cpp \
    src/dnai/enums/qcstandardpaths.cpp \
    src/dnai/http/observable.cpp \
    src/dnai/http/response.cpp \
    src/dnai/http/service.cpp \
    src/dnai/http/url.cpp \
    src/dnai/models/core/entity.cpp \
    src/dnai/models/core/entitydata.cpp \
    src/dnai/models/gui/data/entity.cpp \
    src/dnai/models/gui/declarable/context.cpp \
    src/dnai/models/gui/declarable/enumtype.cpp \
    src/dnai/models/gui/declarable/function.cpp \
    src/dnai/models/gui/declarable/listtype.cpp \
    src/dnai/models/gui/declarable/objecttype.cpp \
    src/dnai/models/gui/declarable/variable.cpp \
    src/dnai/models/gui/flow.cpp \
    src/dnai/models/gui/input.cpp \
    src/dnai/models/gui/instruction.cpp \
    src/dnai/models/gui/output.cpp \
    src/dnai/models/basicnodemodel.cpp \
    src/dnai/models/entity.cpp \
    src/dnai/models/entitytree.cpp \
    src/dnai/models/listnode.cpp \
    src/dnai/models/user.cpp \
    src/dnai/views/appview.cpp \
    src/dnai/views/beziercurve.cpp \
    src/dnai/views/canvasnode.cpp \
    src/dnai/views/console.cpp \
    src/dnai/views/contextview.cpp \
    src/dnai/views/customshape.cpp \
    src/dnai/views/declarationview.cpp \
    src/dnai/views/editorview.cpp \
    src/dnai/views/flow.cpp \
    src/dnai/views/genericnode.cpp \
    src/dnai/views/input.cpp \
    src/dnai/views/instructionview.cpp \
    src/dnai/views/io.cpp \
    src/dnai/views/layout.cpp \
    src/dnai/views/line.cpp \
    src/dnai/views/linkablebezieritem.cpp \
    src/dnai/views/output.cpp \
    src/dnai/views/roundedrectangle.cpp \
    src/dnai/views/viewelement.cpp \
    src/dnai/views/viewzone.cpp \
    src/dnai/app.cpp \
    src/dnai/appcontext.cpp \
    src/dnai/baseio.cpp \
    src/dnai/baselinkable.cpp \
    src/dnai/editor.cpp \
    src/dnai/entitiesfactory.cpp \
    src/dnai/eventutilities.cpp \
    src/dnai/focusmanager.cpp \
    src/dnai/link.cpp \
    src/dnai/processmanager.cpp \
    src/dnai/project.cpp \
    src/dnai/session.cpp \
    src/dnai/settings.cpp \
    src/dnai/solution.cpp \
    src/main.cpp \
    src/dnai/commands/corecommand.cpp \
    src/dnai/core/entitymanager.cpp \
    src/dnai/core/declaratorhandler.cpp \
    src/dnai/core/projecthandler.cpp \
    src/dnai/core/handlermanager.cpp \
    src/dnai/core/variablehandler.cpp \
    src/dnai/core/functionhandler.cpp \
    src/dnai/core/enumhandler.cpp \
    src/dnai/toastermanagerservice.cpp \
    src/dnai/views/toast.cpp \
    src/dnai/models/property.cpp \
    src/dnai/core/instructionhandler.cpp \
    src/dnai/models/contextmenu.cpp \
    src/dnai/models/gui/entitylist.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/local/bin/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dnai.ico

FORMS += \
    resources/Forms/BasePanelForm.ui

#GENERAL HEADER
HEADERS += \
    include/dnai/api/api.h \
    include/dnai/commands/command.h \
    include/dnai/commands/commanddecorator.h \
    include/dnai/commands/commandmanager.h \
    include/dnai/commands/debugdecorator.h \
    include/dnai/commands/genericcommand.h \
    include/dnai/commands/movecanvascommand.h \
    include/dnai/commands/movecommand.h \
    include/dnai/commands/movenodecommand.h \
    include/dnai/commands/openpropertypanel.h \
    include/dnai/commands/zoomcanvascommand.h \
    include/dnai/controllers/consolecontroller.h \
    include/dnai/controllers/inputcontroller.h \
    include/dnai/controllers/outputcontroller.h \
    include/dnai/controllers/propertypanel.h \
    include/dnai/enums/core/instructionid.h \
    include/dnai/enums/declarationtype.h \
    include/dnai/enums/flowtype.h \
    include/dnai/enums/guitype.h \
    include/dnai/enums/iotype.h \
    include/dnai/enums/qcstandardpaths.h \
    include/dnai/exceptions/coreexception.h \
    include/dnai/exceptions/exception.h \
    include/dnai/exceptions/exceptionmanager.h \
    include/dnai/exceptions/guiexception.h \
    include/dnai/exceptions/notimplemented.h \
    include/dnai/http/config.h \
    include/dnai/http/interceptor.h \
    include/dnai/http/observable.h \
    include/dnai/http/response.h \
    include/dnai/http/service.h \
    include/dnai/http/types.h \
    include/dnai/http/url.h \
    include/dnai/interfaces/iclone.h \
    include/dnai/interfaces/icommand.h \
    include/dnai/interfaces/icontroller.h \
    include/dnai/interfaces/ieditor.h \
    include/dnai/interfaces/ieditoraction.h \
    include/dnai/interfaces/ieditormodel.h \
    include/dnai/interfaces/ientity.h \
    include/dnai/interfaces/ifactory.h \
    include/dnai/interfaces/iinstruction.h \
    include/dnai/interfaces/ilinkable.h \
    include/dnai/interfaces/iloadingclass.h \
    include/dnai/interfaces/imodel.h \
    include/dnai/interfaces/imodeldata.h \
    include/dnai/interfaces/iobservable.h \
    include/dnai/interfaces/iproject.h \
    include/dnai/interfaces/isavable.h \
    include/dnai/interfaces/iscalable.h \
    include/dnai/interfaces/iserializable.h \
    include/dnai/interfaces/isingleton.h \
    include/dnai/interfaces/isolution.h \
    include/dnai/interfaces/ivariable.h \
    include/dnai/interfaces/iviewelement.h \
    include/dnai/interfaces/iviewzone.h \
    include/dnai/models/core/entity.h \
    include/dnai/models/core/entitydata.h \
    include/dnai/models/gui/data/context.h \
    include/dnai/models/gui/data/entity.h \
    include/dnai/models/gui/data/entitycolum.h \
    include/dnai/models/gui/data/enumtype.h \
    include/dnai/models/gui/data/flow.h \
    include/dnai/models/gui/data/function.h \
    include/dnai/models/gui/data/input.h \
    include/dnai/models/gui/data/instruction.h \
    include/dnai/models/gui/data/linkable.h \
    include/dnai/models/gui/data/listtype.h \
    include/dnai/models/gui/data/objecttype.h \
    include/dnai/models/gui/data/output.h \
    include/dnai/models/gui/data/variable.h \
    include/dnai/models/gui/declarable/context.h \
    include/dnai/models/gui/declarable/entity.h \
    include/dnai/models/gui/declarable/enumtype.h \
    include/dnai/models/gui/declarable/function.h \
    include/dnai/models/gui/declarable/listtype.h \
    include/dnai/models/gui/declarable/objecttype.h \
    include/dnai/models/gui/declarable/variable.h \
    include/dnai/models/gui/flow.h \
    include/dnai/models/gui/input.h \
    include/dnai/models/gui/instruction.h \
    include/dnai/models/gui/output.h \
    include/dnai/models/basicnodemodel.h \
    include/dnai/models/entity.h \
    include/dnai/models/entitytree.h \
    include/dnai/models/generictreeitem.h \
    include/dnai/models/guicorestruct.h \
    include/dnai/models/instruction.h \
    include/dnai/models/listnode.h \
    include/dnai/models/user.h \
    include/dnai/utils/cx_string.h \
    include/dnai/utils/cx_stringlist.h \
    include/dnai/views/appview.h \
    include/dnai/views/beziercurve.h \
    include/dnai/views/borderlesswindow.h \
    include/dnai/views/canvasnode.h \
    include/dnai/views/console.h \
    include/dnai/views/contextview.h \
    include/dnai/views/customshape.h \
    include/dnai/views/declarationview.h \
    include/dnai/views/editorview.h \
    include/dnai/views/flow.h \
    include/dnai/views/genericnode.h \
    include/dnai/views/input.h \
    include/dnai/views/instructionview.h \
    include/dnai/views/io.h \
    include/dnai/views/layout.h \
    include/dnai/views/line.h \
    include/dnai/views/linkablebezieritem.h \
    include/dnai/views/output.h \
    include/dnai/views/roundedrectangle.h \
    include/dnai/views/viewelement.h \
    include/dnai/views/viewzone.h \
    include/dnai/app.h \
    include/dnai/appcontext.h \
    include/dnai/baseio.h \
    include/dnai/baselinkable.h \
    include/dnai/editor.h \
    include/dnai/entitiesfactory.h \
    include/dnai/eventutilities.h \
    include/dnai/focusmanager.h \
    include/dnai/link.h \
    include/dnai/linkablebezieritem.h \
    include/dnai/linkabletype.h \
    include/dnai/processmanager.h \
    include/dnai/project.h \
    include/dnai/session.h \
    include/dnai/settings.h \
    include/dnai/solution.h \
    include/api.h \
    include/commands.h \
    include/controllers.h \
    include/enums.h \
    include/http.h \
    include/models.h \
    include/views.h \
    include/dnai/commands/corecommand.h \
    include/dnai/core/entitymanager.h \
    include/dnai/core/declaratorhandler.h \
    include/dnai/core/variablehandler.h \
    include/dnai/core/functionhandler.h \
    include/dnai/core/enumhandler.h \
    include/dnai/core/listhandler.h \
    include/dnai/core/objecthandler.h \
    include/dnai/core/projecthandler.h \
    include/dnai/views/viewelement.h \
    include/dnai/views/viewzone.h \
    include/dnai/views/editorview.h \
    include/dnai.h \
    include/exceptions.h \
    include/interfaces.h \
    include/dnai/core/handlermanager.h \
    $${PWD}/../lib/lcore_client/include/core.h \
    include/dnai/toastermanagerservice.h \
    include/dnai/views/toast.h \
    include/dnai/models/property.h \
    include/dnai/core/instructionhandler.h \
    include/dnai/models/gui/entitylist.h \
    include/dnai/models/contextmenu.h \
    include/dnai/core/instructionmanager.h


#LIB
DEPENDPATH += $${PWD}/../lib/
INCLUDEPATH += $${PWD}/../lib/lcore_client/include/

win32-msvc*{
    DEPENDPATH += $${PWD}/../lib/lwintoast/
    LIBS += -lwintoast
} win32-g++ {
} macx-clang* {
#QT += core
#QT += macextras
#QT += gui
    #DEPENDPATH += $${PWD}/../lib/MACToast/
    #LIBS +=  -lMACToast
    #LIBS += -framework Foundation
    #INCLUDEPATH += /System/Library/Frameworks/Foundation.framework/Versions/C/Headers
}


#begin library network
LIBS += -L$${PWD}/../lib/ -lcore_client -levent_client -lcerealization

#-lDataComEvent

#CONFIG(release, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobuf
#}
#CONFIG(debug, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobufd
#}

#end library Data Event
CONFIG(release, debug|release) {
win32:settingsfolder.path = $${OUT_PWD}/release/settings
}
CONFIG(debug, debug|release) {
win32:settingsfolder.path = $${OUT_PWD}/debug/settings
}

unix:settingsfolder.path = /usr/local/bin/$${TARGET}/bin/$${TARGET}.app/Contents/MacOS/settings
settingsfolder.files = settings/*

#settingsfolderconf.path = $${OUT_PWD}/settings/conf
#settingsfolderconf.files = settings/conf/*/*

INSTALLS += settingsfolder
