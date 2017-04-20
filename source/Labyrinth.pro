#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# Labyrinth
# Authors: Karimov Konstantin, Karimov Ashat,
# Karimova Lidiya
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG   += ordered

SUBDIRS = \
            GlobalModel     \
            EngineModule    \
            GraphicsModule  \
            App

App.depends = GlobalModel EngineModule GraphicsModule
GraphicsModule.depends = GlobalModel EngineModule

QMAKE_CXXFLAGS    += -std=c++11 -Wall -Wextra -g
