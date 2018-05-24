TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = libReseau libCerealization libCoreClient

libReseau.file = levent_client/levent_client.pro
libCerealization.file = lcerealization/lcerealization.pro
libCoreClient.file = lcore_client/lcore_client.pro

libCoreClient.depends = libReseau libCerealization

win32-msvc* {
    SUBDIRS += notiflib
    notiflib.file = lwintoast/lwintoast.pro
    app.depends = notiflib libCoreClient
}
macx-clang* {
    SUBDIRS += notifmac
    notifmac.file = lmactoast/lmactoast.pro
    app.depends = notifmac libCoreClient
}
