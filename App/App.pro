#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# Labyrinth
# Authors: Karimov Konstantin, Karimov Ashat
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11
QMAKE_LFLAGS    += -fopenmp

DESTDIR     = "../../Labyrinth_build/Out"
OBJECTS_DIR = "../../Labyrinth_build/"$$TARGET"/Objects"
MOC_DIR     = "../../Labyrinth_build/"$$TARGET"/MOCs"
RCC_DIR     = "../../Labyrinth_build/"$$TARGET"/RCCs"
UI_DIR      = "../../Labyrinth_build/"$$TARGET"/UIs"

TARGET = Labyrinth
TEMPLATE = app


SOURCES  += main.cpp \
            labymainwindow.cpp \
            aboutwindow.cpp \
    settingswindow.cpp


HEADERS  += labymainwindow.h \
            globals.h \
            aboutwindow.h \
    settingswindow.h

FORMS    += labymainwindow.ui \
            aboutwindow.ui \
    settingswindow.ui


INCLUDEPATH +=  "../GraphicsModule" \
                "../GlobalModel"

LIBS += $$DESTDIR/GraphicsModule.dll \
        $$DESTDIR/GlobalModel.dll

RESOURCES += icons/iconres.qrc
