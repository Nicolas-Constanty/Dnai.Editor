TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = app libReseau libCerealization libCoreClient

app.file = app/dnai_app.pro
libReseau.file = lib/levent_client/levent_client.pro
libCerealization.file = lib/lcerealization/lcerealization.pro
libCoreClient.file = lib/lcore_client/lcore_client.pro

libCoreClient.depends = libReseau libCerealization

win32-msvc* {
    SUBDIRS += notiflib
    notiflib.file = lib/lwintoast/lwintoast.pro
    app.depends = notiflib libCoreClient
}
macx-clang* {
    SUBDIRS += notifmac
    notifmac.file = lib/lmactoast/lmactoast.pro
    app.depends = notifmac libCoreClient
}
win32-g++ {
    app.depends = libCoreClient
}
unix:!macx {
    app.depends = libCoreClient
}
