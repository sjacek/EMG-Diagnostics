QMAKE_PROJECT_NAME = libQuECG
#TARGET = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})
TARGET = QuECG

QT -= gui

TEMPLATE = lib
DEFINES += LIBQUECG_LIBRARY

CONFIG += c++17 rtti precompile_header extserialport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch_libquecg.h

SOURCES += \
    ecgdata.cpp \
    uartport.cpp \
    uecgenumerator.cpp

HEADERS += \
    ecgdata.h \
    libquecg_global.h \
    uartport.h \
    uecgenumerator.h

OTHER_FILES += \
    libQuECG.pri

#INCLUDEPATH += $$TOP_SRCDIR/3rdparty/qextserialport/src
#DEPENDPATH += $$TOP_SRCDIR/3rdparty/qextserialport/src
#LIBS += -L$$LIB_DESTDIR -lQt5ExtSerialPort

#CONFIG += qesp_linux_udev
#include($$TOP_SRCDIR/3rdparty/qextserialport/src/qextserialport.pri)

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

defined(LIB_DESTDIR, var) {
    DESTDIR = $${LIB_DESTDIR}
}
