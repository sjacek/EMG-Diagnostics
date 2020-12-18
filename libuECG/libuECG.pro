QMAKE_PROJECT_NAME = libuECG
#TARGET = $$qtLibraryTarget($${QMAKE_PROJECT_NAME})
TARGET = uECG

CONFIG -= qt

TEMPLATE = lib
DEFINES += LIBUECG_LIBRARY

#CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    device_functions.c \
    packet_parser.c \
    serial_functions.c

HEADERS += \
    definitions.h \
    device_functions.h \
    packet_parser.h \
    serial_functions.h \
    uecg.h \
    uecg_global.h \
    uecg_version.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = $${LIB_DIR}
