TEMPLATE = subdirs
SUBDIRS = app libtoast libReseau libDataEvent

CONFIG += object_parallel_to_source

app.file = app/dnai_app.pro

libtoast.file = lib/WinToast/wintoast.pro
libReseau.file = lib/event_client/event_client.pro
libDataEvent.file = lib/DataComEvent/DataComEvent.pro

app.depends = libtoast libReseau libDataEvent
