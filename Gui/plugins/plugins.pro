TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = libSettings libFontAwesome libControl libTheme

libSettings.file = Settings/lsettings.pro
libControl.file = Controls/lcontrols.pro
libFontAwesome.file = FontAwesome/lfontawesome.pro
libTheme.file = Theme/ltheme.pro

libControl.depends = libFontAwesome
libTheme.depends = libControl libSettings
