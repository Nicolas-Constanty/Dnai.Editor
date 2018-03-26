TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = app libReseau libCerealization libCoreClient

app.file = app/dnai_app.pro
libReseau.file = lib/event_client/event_client.pro
libCerealization.file = lib/Cerealization/Cerealization.pro
libCoreClient.file = lib/core_client/core_client.pro

libCoreClient.depends = libReseau libCerealization
app.depends = libCoreClient

win32-msvc* {
    SUBDIRS += notiflib
    notiflib.file = lib/WinToast/wintoast.pro
    app.depends += notiflib
}
macx-clang* {
    SUBDIRS += notifmac
    notifmac.file = lib/MACToast/MACToast.pro
    app.depends = notifmac
}
win32-g++ {

}
unix:!macx {

}
