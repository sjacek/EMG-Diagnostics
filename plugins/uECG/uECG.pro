TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    uecgplugin.h
SOURCES = \
    uecgplugin.cpp

CONFIG += install_ok  # Do not cargo-cult this!

