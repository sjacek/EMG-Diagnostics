QMAKE_PROJECT_NAME = EMG-Diagnostics

BUILD_ROOT_DIR=$${OUT_PWD}/../App
SRC_ROOT_DIR=$${PWD}/..

# Check if the config file exists
! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}


QT += charts qml quick

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    datasource.h \
    emgviewer.h

SOURCES += \
    datasource.cpp \
    emgviewer.cpp \
    main.cpp

RESOURCES += qml.qrc

DISTFILES += \
    qml/ControlPanel.qml \
    qml/MultiButton.qml \
    qml/ScopeView.qml \
    qml/emgviewer.qml


TRANSLATIONS += \
    EMG-Diagnostics_en_GB.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${QMAKE_PROJECT_NAME}/bin
else: unix:!android: target.path = /opt/$${QMAKE_PROJECT_NAME}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$${LIB_DIR}/release/ -l$${INTERFACE_LIB_NAME}
else:win32:CONFIG(debug, debug|release): LIBS += -L$${LIB_DIR}/debug/ -l$${INTERFACE_LIB_NAME}
else:unix: LIBS += -L$${LIB_DIR} -l$${INTERFACE_LIB_NAME}

#INCLUDEPATH += $$PWD/../plugins/$${INTERFACE_SRC_NAME}
#DEPENDPATH += $$PWD/../plugins/$${INTERFACE_SRC_NAME}

DISTFILES +=

DESTDIR = $${APP_DIR}

CONFIG += install_ok  # Do not cargo-cult this!
