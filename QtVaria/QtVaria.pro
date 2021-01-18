QMAKE_PROJECT_NAME = QtVaria
#TARGET = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})

QT -= gui

TEMPLATE = lib
DEFINES += QTVARIA_LIBRARY

CONFIG += c++17 rtti precompile_header

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = pch_qtvaria.h

SOURCES += \
    qtvaria.cpp \
    qvexception.cpp

HEADERS += \
    QtVaria_global.h \
    pch_qtvaria.h \
    qtvaria.h \
    qvexception.h \
    singleton.h

OTHER_FILES += \
    QtVaria.pri

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

defined(LIB_DESTDIR, var) {
    DESTDIR = $${LIB_DESTDIR}
}
