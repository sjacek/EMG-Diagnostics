# Check if the plugin config file exists
! include( ../plugin.pri ) {
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    uecgplugin.h
SOURCES = \
    uecgplugin.cpp

CONFIG += install_ok  # Do not cargo-cult this!

TARGET  = $$qtLibraryTarget(uECG)
#DESTDIR = ../plugins

CONFIG += install_ok  # Do not cargo-cult this!
