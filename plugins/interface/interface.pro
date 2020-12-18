QMAKE_PROJECT_NAME = interface

! include( $$TOP_SRCDIR/plugins/plugins.pri ) {
    error( "Couldn't find the plugins/plugins.pri file!" )
}

QT -= gui

TARGET  = $${INTERFACE_LIB_NAME}
#TARGET  = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})

TEMPLATE = lib

DEFINES += INTERFACEPLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# overwritten common.pri
PRECOMPILED_HEADER = \
    pch_interface.h

SOURCES += \
    pluginsocket.cpp

HEADERS += \
        pch_interface.h \
        plugin.h \
        plugin_global.h \
        singleton.h \
        pluginsocket.h \
        dataseries.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $${LIB_DIR}

CONFIG += install_ok  # Do not cargo-cult this!
