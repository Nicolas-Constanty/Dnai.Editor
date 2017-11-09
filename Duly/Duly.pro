TEMPLATE = subdirs
SUBDIRS = app lib

app.file = app/duly_app.pro

lib.file = lib/event_client/event_client.pro

app.depends = lib
