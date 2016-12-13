#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# 
#-------------------------------------------------

QT       += core gui widgets

TARGET = GraphicsModule
TEMPLATE = lib

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11

DEFINES += GRAPHICSMODULE_LIBRARY

DESTDIR     = "../../Labyrinth_build/Out"
OBJECTS_DIR = "../../Labyrinth_build/"$$TARGET"/Objects"
MOC_DIR     = "../../Labyrinth_build/"$$TARGET"/MOCs"
RCC_DIR     = "../../Labyrinth_build/"$$TARGET"/RCCs"
UI_DIR      = "../../Labyrinth_build/"$$TARGET"/UIs"


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

LIBS += $$DESTDIR"/GlobalModel.dll"
