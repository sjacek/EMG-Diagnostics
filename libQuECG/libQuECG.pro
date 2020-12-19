QMAKE_PROJECT_NAME = libQuECG
#TARGET = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})
TARGET = QuECG

QT -= gui

TEMPLATE = lib
DEFINES += LIBQUECG_LIBRARY
#include(libQuECG.pri)

CONFIG += c++17 rtti precompile_header

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch_libquecg.h

SOURCES += \
    uecg.cpp

HEADERS += \
    libquecg_global.h \
    uecg.h

OTHER_FILES += \
    libQuECG.pri

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
