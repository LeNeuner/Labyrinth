#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# Labyrinth
# Authors: Karimov Konstantin, Karimov Ashat
# Karimova Lidiya
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11
QMAKE_LFLAGS    += -fopenmp

#TARGET = Labyrinth
TEMPLATE = app

CONFIG (debug, debug|release) {
    TARGET      = Labyrinth_d
    DESTDIR     = "../../debug"
    OBJECTS_DIR = "../../Labyrinth_debug/"$$TARGET"/Objects"
    MOC_DIR     = "../../Labyrinth_debug/"$$TARGET"/MOCs"
    RCC_DIR     = "../../Labyrinth_debug/"$$TARGET"/RCCs"
    UI_DIR      = "../../Labyrinth_debug/"$$TARGET"/UIs"

LIBS += $$DESTDIR/GraphicsModule_d.dll \
        $$DESTDIR/GlobalModel_d.dll
} else {
    TARGET = Labyrinth
    DESTDIR     = "../../build"
    OBJECTS_DIR = "../../Labyrinth_build/"$$TARGET"/Objects"
    MOC_DIR     = "../../Labyrinth_build/"$$TARGET"/MOCs"
    RCC_DIR     = "../../Labyrinth_build/"$$TARGET"/RCCs"
    UI_DIR      = "../../Labyrinth_build/"$$TARGET"/UIs"

LIBS += $$DESTDIR/GraphicsModule.dll \
        $$DESTDIR/GlobalModel.dll
}


SOURCES  += main.cpp            \
            labymainwindow.cpp  \
            aboutwindow.cpp     \
            settingswindow.cpp


HEADERS  += labymainwindow.h    \
            globals.h           \
            aboutwindow.h       \
            settingswindow.h

FORMS    += labymainwindow.ui   \
            aboutwindow.ui      \
            settingswindow.ui


INCLUDEPATH +=  "../GraphicsModule" \
                "../GlobalModel"

RESOURCES   += icons/iconres.qrc
RC_FILE     += icons/mainiconres.rc
