TEMPLATE = subdirs
SUBDIRS = app libReseau libDataEvent

CONFIG += object_parallel_to_source

app.file = app/duly_app.pro

libReseau.file = lib/event_client/event_client.pro
libDataEvent.file = lib/DataComEvent/DataComEvent.pro
splashScreen.file = app/SplashScreen/SplashScreen.pro

app.depends = libReseau libDataEvent
