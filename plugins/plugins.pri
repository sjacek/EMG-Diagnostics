# Check if the config file exists
! include( $$TOP_SRCDIR/common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

DEFINES += BUILD_NAME=\\\"$${TARGET}\\\"

## Default rules for plugins deployment.
#qnx: target.path = /tmp/$${QMAKE_PROJECT_NAME}/lib/plugins
#else: unix:!android: target.path = /opt/$${QMAKE_PROJECT_NAME}//lib/plugins
#!isEmpty(target.path): INSTALLS += target

DESTDIR = $${PLUGINS_DIR}
