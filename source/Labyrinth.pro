#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T11:38:09
# Labyrinth
# Authors: Karimov Konstantin, Karimov Ashat
#-------------------------------------------------

TEMPLATE = subdirs
CONFIG   += ordered

SUBDIRS = \
            GlobalModel       \
#            SettingsModule    \
            GraphicsModule    \
            App

App.depends = GlobalModel GraphicsModule
GraphicsModule.depends = GlobalModel

#App.depends = GlobalModel SettingsModule GraphicsModule
#GraphicsModule.depends = SettingsModule GlobalModel
#settingsModule.depends = GlobalModel

QMAKE_CXXFLAGS    += -std=c++11 -Wall -Wextra -g
