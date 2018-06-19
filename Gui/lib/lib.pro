TEMPLATE = subdirs
CONFIG += object_parallel_to_source

SUBDIRS = libReseau libCerealization libCoreClient

libReseau.file = levent_client/levent_client.pro
libCerealization.file = lcerealization/lcerealization.pro
libCoreClient.file = lcore_client/lcore_client.pro

libCoreClient.depends = libReseau libCerealization
