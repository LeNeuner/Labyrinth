#-------------------------------------------------
#
# EngineModule - game engine functional
#
#-------------------------------------------------
include(../../common.pri)
include(../../lib.pri)

QT       += core gui widgets

TARGET = EngineModule$${LIB_SUFFIX}
TEMPLATE = lib

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11

DEFINES += ENGINEMODULE_LIBRARY

SOURCES  += enginemanager.cpp

HEADERS  += enginemanager.h       \
            enginemodule_global.h

INCLUDEPATH +=  "../GlobalModel"

LIBS += -lGlobalModel$${LIB_SUFFIX}
