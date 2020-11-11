# Check if the plugin config file exists
! include( ../plugin.pri ) {
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    fakeplugin.h
SOURCES = \
    fakeplugin.cpp

TARGET  = $$qtLibraryTarget(fake)
#DESTDIR = ../plugins

CONFIG += install_ok  # Do not cargo-cult this!
