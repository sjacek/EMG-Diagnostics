BUILD_ROOT_DIR=$${OUT_PWD}/../../App
SRC_ROOT_DIR=$${PWD}/../..

# Check if the config file exists
! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

DEFINES += BUILD_NAME=\\\"$${TARGET}\\\"

## Default rules for plugins deployment.
#qnx: target.path = /tmp/$${QMAKE_PROJECT_NAME}/lib/plugins
#else: unix:!android: target.path = /opt/$${QMAKE_PROJECT_NAME}//lib/plugins
#!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$${LIB_DIR}/release/ -l$${INTERFACE_LIB_NAME}
else:win32:CONFIG(debug, debug|release): LIBS += -L$${LIB_DIR}/debug/ -l$${INTERFACE_LIB_NAME}
else:unix: LIBS += -L$${LIB_DIR} -l$${INTERFACE_LIB_NAME}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../$${INTERFACE_SRC_NAME}
DEPENDPATH += $$PWD/../$${INTERFACE_SRC_NAME}

DESTDIR = $${PLUGINS_DIR}
