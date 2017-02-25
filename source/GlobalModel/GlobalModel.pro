#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------
QT += core gui widgets

#TARGET   = GlobalModel
TEMPLATE = lib

CONFIG += c++11

DEFINES += GLOBALMODEL_LIBRARY

CONFIG (debug, debug|release) {
      TARGET      = GlobalModel_d
      DESTDIR     = "../../debug"
      OBJECTS_DIR = "../../Labyrinth_debug/"$$TARGET"/Objects"
      MOC_DIR     = "../../Labyrinth_debug/"$$TARGET"/MOCs"
      RCC_DIR     = "../../Labyrinth_debug/"$$TARGET"/RCCs"
      UI_DIR      = "../../Labyrinth_debug/"$$TARGET"/UIs"
} else {
      TARGET      = GlobalModel
      DESTDIR     = "../../build"
      OBJECTS_DIR = "../../Labyrinth_build/"$$TARGET"/Objects"
      MOC_DIR     = "../../Labyrinth_build/"$$TARGET"/MOCs"
      RCC_DIR     = "../../Labyrinth_build/"$$TARGET"/RCCs"
      UI_DIR      = "../../Labyrinth_build/"$$TARGET"/UIs"
}

HEADERS += \
            globalModel_global.h    \
            globalmodel.h           \
#            connkeeper.h            \
#            commessagekeeper.h      \
#            hotkeykeeper.h          \
#            settingslimits.h        \
#            hotkey.h                \
#            message.h
            cell.h                  \
            field.h                 \
            gamesettings.h          \
            settingslimits.h

SOURCES += \
            globalmodel.cpp         \
#            connkeeper.cpp          \
#            commessagekeeper.cpp    \
#            hotkeykeeper.cpp
            cell.cpp                \
            field.cpp               \
            gamesettings.cpp

