#-------------------------------------------------
#
# GraphicsModule - qt graphics functional
# 
#-------------------------------------------------
include(../../common.pri)
include(../../lib.pri)

QT       += core gui widgets

TARGET = GraphicsModule$${LIB_SUFFIX}
TEMPLATE = lib

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11

DEFINES += GRAPHICSMODULE_LIBRARY

SOURCES  += graphicsmanager.cpp     \
            labygraphicsscene.cpp   \
            basicrect.cpp           \
            pixmapkeeper.cpp

HEADERS  += graphicsmanager.h       \
            labygraphicsscene.h     \
            graphicsmodule_global.h \
            basicrect.h             \
            pixmapkeeper.h

RESOURCES += labyresources.qrc

INCLUDEPATH +=  "../GlobalModel"

LIBS += -lGlobalModel$${LIB_SUFFIX}
