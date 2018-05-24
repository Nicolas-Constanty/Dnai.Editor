TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = libFontAwesome libControl

libControl.file = Controls/lcontrols.pro
libFontAwesome.file = FontAwesome/lfontawesome.pro

libControl.depends = libFontAwesome
