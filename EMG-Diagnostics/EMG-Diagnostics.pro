QMAKE_PROJECT_NAME = EMG-Diagnostics

# Check if the config file exists
! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT += charts qml quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH    += ../plugins/interface

HEADERS += \
    ../plugins/interface/dataseries.h \
    ../plugins/interface/plugin.h \
    datasource.h \
    emgapplication.h \
    emgviewer.h

SOURCES += \
    datasource.cpp \
    emgapplication.cpp \
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

CONFIG += install_ok  # Do not cargo-cult this!
