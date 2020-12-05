BUILD_ROOT_DIR=$${OUT_PWD}/../../App

# Check if the config file exists
! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

DEFINES += BUILD_NAME=\\\"$${TARGET}\\\"

## Default rules for plugins deployment.
#qnx: target.path = /tmp/$${QMAKE_PROJECT_NAME}/lib/plugins
#else: unix:!android: target.path = /opt/$${QMAKE_PROJECT_NAME}//lib/plugins
#!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/$${INTERFACE_SRC_NAME}
DEPENDPATH += $$PWD/$${INTERFACE_SRC_NAME}

DESTDIR = $${PLUGINS_DIR}