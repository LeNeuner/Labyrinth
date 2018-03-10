#-------------------------------------------------
# Project created by QtCreator 2016-09-10T11:38:09
# Labyrinth
# Authors: Karimov Konstantin, Karimov Ashat
# Karimova Lidiya
#-------------------------------------------------
include(../../common.pri)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG          += c++11
QMAKE_CXXFLAGS  += -std=c++11
QMAKE_LFLAGS    += -fopenmp

TARGET = Labyrinth
TEMPLATE = app

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

DESTDIR = $${BIN_PATH}/

LIBS += -lGraphicsModule$${LIB_SUFFIX} \
       	-lGlobalModel$${LIB_SUFFIX}
