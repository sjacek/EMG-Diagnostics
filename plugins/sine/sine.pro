QMAKE_PROJECT_NAME = sine
TARGET  = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})

! include( $$TOP_SRCDIR/plugins/plugins.pri ) {
    error( "Couldn't find the plugins/plugins.pri file!" )
}
! include( $$TOP_SRCDIR/plugins/interface/interface.pri ) {
    error( "Couldn't find the plugins/interface/interface.pri file!" )
}

QT -= gui

TEMPLATE = lib

CONFIG += plugin rtti c++17 precompile_header

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch.h

HEADERS = \
    pch.h \
    renderthread.h \
    sineplugin.h \
    sineseries.h

SOURCES = \
    renderthread.cpp \
    sineplugin.cpp \
    sineseries.cpp

DISTFILES += \
    sineplugin.json

LIBS += -L$${LIB_DIR} -l$${INTERFACE_LIB_NAME}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG += install_ok  # Do not cargo-cult this!
