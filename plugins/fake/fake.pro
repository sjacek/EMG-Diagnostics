TEMPLATE = lib

CONFIG += plugin
QT += widgets
INCLUDEPATH    += ../interface

HEADERS = \
    fakeplugin.h
SOURCES = \
    fakeplugin.cpp

CONFIG += install_ok  # Do not cargo-cult this!

