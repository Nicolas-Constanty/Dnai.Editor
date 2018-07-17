TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = app qtplugins lib

app.file = app/app.pro
lib.file = lib/lib.pro

qtplugins.file = plugins/plugins.pro

app.depends = qtplugins lib
