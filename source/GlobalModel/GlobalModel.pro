#-------------------------------------------------
#
# GlobalModel - model with main parameters
#
#-------------------------------------------------
include(../../common.pri)
include(../../lib.pri)

QT += core gui widgets

TARGET   = GlobalModel$${LIB_SUFFIX}
TEMPLATE = lib

CONFIG += c++11
QMAKE_CXXFLAGS  += -std=c++11

DEFINES += GLOBALMODEL_LIBRARY

HEADERS += \
            globalModel_global.h    \
            globalmodel.h           \
            cell.h                  \
            field.h                 \
            gamesettings.h          \
            position.h              \
            player.h                \
            constlist.h             \
            errorslist.h            \
            playercellinfo.h        \
            playerfieldinfo.h

SOURCES += \
            globalmodel.cpp         \
            cell.cpp                \
            field.cpp               \
            gamesettings.cpp        \
            player.cpp              \
            playercellinfo.cpp      \
            playerfieldinfo.cpp

win32 {
    QMAKE_TARGET_PRODUCT = GlobalModel.dll 
    QMAKE_TARGET_DESCRIPTION = Dll with main parameters
}
