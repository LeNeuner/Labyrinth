#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# 
#-------------------------------------------------

QT       += core gui widgets

#TARGET = GraphicsModule
TEMPLATE = lib

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11

DEFINES += GRAPHICSMODULE_LIBRARY

CONFIG (debug, debug|release) {
    TARGET      = GraphicsModule_d
    DESTDIR     = "../../debug"
    OBJECTS_DIR = "../../Labyrinth_debug/"$$TARGET"/Objects"
    MOC_DIR     = "../../Labyrinth_debug/"$$TARGET"/MOCs"
    RCC_DIR     = "../../Labyrinth_debug/"$$TARGET"/RCCs"
    UI_DIR      = "../../Labyrinth_debug/"$$TARGET"/UIs"

    LIBS += $$DESTDIR"/GlobalModel_d.dll"
} else {
    TARGET      = GraphicsModule
    DESTDIR     = "../../build"
    OBJECTS_DIR = "../../Labyrinth_build/"$$TARGET"/Objects"
    MOC_DIR     = "../../Labyrinth_build/"$$TARGET"/MOCs"
    RCC_DIR     = "../../Labyrinth_build/"$$TARGET"/RCCs"
    UI_DIR      = "../../Labyrinth_build/"$$TARGET"/UIs"

    LIBS += $$DESTDIR"/GlobalModel.dll"
}


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


