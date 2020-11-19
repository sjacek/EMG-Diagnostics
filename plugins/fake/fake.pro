QMAKE_PROJECT_NAME = fake
TARGET  = $$qtLibraryTarget(fake)

# Check if the plugin config file exists
! include( ../plugin.pri ) {
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    fakeplugin.h \
    fakeseries.h
SOURCES = \
    fakeplugin.cpp \
    fakeseries.cpp

DISTFILES += \
    fakeplugin.json

CONFIG += install_ok  # Do not cargo-cult this!
