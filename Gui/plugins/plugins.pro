TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = libSettings libFontAwesome libControl

libSettings.file = Settings/lsettings.pro
libControl.file = Controls/lcontrols.pro
libFontAwesome.file = FontAwesome/lfontawesome.pro

libControl.depends = libFontAwesome
