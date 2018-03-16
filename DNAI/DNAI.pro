TEMPLATE = subdirs
CONFIG += object_parallel_to_source

win32-msvc* {
    SUBDIRS = app notiflib libReseau libDataEvent libCerealization
    app.file = app/dnai_app.pro
    notiflib.file = lib/WinToast/wintoast.pro
    libReseau.file = lib/event_client/event_client.pro
    libDataEvent.file = lib/DataComEvent/DataComEvent.pro
    libCerealization.file = lib/Cerealization/Cerealization.pro
    app.depends = notiflib libReseau libDataEvent libCerealization
} macx-clang* {
    SUBDIRS = app notifmac libReseau libDataEvent
    app.file = app/dnai_app.pro
    notifmac.file = lib/MACToast/MACToast.pro
    libReseau.file = lib/event_client/event_client.pro
    libDataEvent.file = lib/DataComEvent/DataComEvent.pro
    app.depends = notifmac libReseau libDataEvent
} win32-g++ {
    SUBDIRS = app libReseau libDataEvent
    app.file = app/dnai_app.pro
    libReseau.file = lib/event_client/event_client.pro
    libDataEvent.file = lib/DataComEvent/DataComEvent.pro
    app.depends = libReseau libDataEvent
} unix:!macx {
    SUBDIRS = app libReseau libDataEvent
    app.file = app/dnai_app.pro
    libReseau.file = lib/event_client/event_client.pro
    libDataEvent.file = lib/DataComEvent/DataComEvent.pro
    app.depends = libReseau libDataEvent
}
