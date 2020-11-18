QMAKE_PROJECT_NAME = uECG-plugin

# Check if the plugin config file exists
! include( ../plugin.pri ) {
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    uecgplugin.h \
    uecgseries.h
SOURCES = \
    uecgplugin.cpp \
    uecgseries.cpp

TARGET  = $$qtLibraryTarget(uECG)
#DESTDIR = ../plugins

CONFIG += install_ok  # Do not cargo-cult this!
