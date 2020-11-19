QMAKE_PROJECT_NAME = uECG-plugin
TARGET  = $$qtLibraryTarget(uECG)

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

DISTFILES += \
    uecgplugin.json

CONFIG += install_ok  # Do not cargo-cult this!
