# Created by and for Qt Creator. This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = Cerealization
CONFIG += staticlib
CONFIG += c++14
DESTDIR = $$PWD/../

TEMPLATE = lib

CEREAL_ROOT = $$PWD/repository

INCLUDE_ROOT = $$CEREAL_ROOT/include
SRC_ROOT = $$CEREAL_ROOT/src

HEADERS = \
    $$INCLUDE_ROOT/Cerealizable/Data.hpp \
    $$INCLUDE_ROOT/Cerealizable/DataDecl.hpp \
    $$INCLUDE_ROOT/Cerealizable/List.hpp \
    $$INCLUDE_ROOT/Cerealizable/Object.hpp \
    $$INCLUDE_ROOT/Cerealizable/Scalar.hpp \
    $$INCLUDE_ROOT/Cerealizable/Tuple.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/Binary.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/BinaryObject.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/BinaryStream.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/BinaryTuple.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/DefaultOperations.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/ModelOperations.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/Operations.hpp \
    $$INCLUDE_ROOT/Cerealizer/Binary/StructOperations.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/DefaultOperations.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/JSON.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/JSONObject.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/JSONStream.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/JSONTuple.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/ModelOperations.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/Operations.hpp \
    $$INCLUDE_ROOT/Cerealizer/JSON/StructOperations.hpp

SOURCES = \
    repository/src/Binary/BinaryOperations.cpp \
    repository/src/Binary/BinaryStream.cpp \
    repository/src/JSON/JSONOperations.cpp \
    repository/src/JSON/JSONStream.cpp

INCLUDEPATH = $$INCLUDE_ROOT

#DEFINES = 

