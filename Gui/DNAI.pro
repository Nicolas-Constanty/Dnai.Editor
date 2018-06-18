TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = app qtplugins lib

app.file = app/app.pro
lib.file = lib/lib.pro

qtplugins.file = plugins/plugins.pro

win32-g++ {
    app.depends = qtplugins lib
}
unix:!macx {
    app.depends = qtplugins lib
}
