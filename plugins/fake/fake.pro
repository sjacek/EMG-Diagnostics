QMAKE_PROJECT_NAME = fake
TARGET  = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})

# Check if the config file exists
! include( ../plugins.pri ) {
    error( "Couldn't find the plugins.pri file!" )
}

QT -= gui

TEMPLATE = lib

CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS = \
    fakeplugin.h \
    fakeseries.h
SOURCES = \
    fakeplugin.cpp \
    fakeseries.cpp

DISTFILES += \
    fakeplugin.json

CONFIG += install_ok  # Do not cargo-cult this!
