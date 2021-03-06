QMAKE_PROJECT_NAME = EMG-Diagnostics

QT += charts qml quick

CONFIG += rtti c++17 precompile_header log4qt

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# currently it's not working thus commented out
CONFIG += qmltypes
QML_IMPORT_NAME = com.github.sjacek.emgdiagnostics
QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_MINOR_VERSION = 0

DEFINES += QT_MESSAGELOGCONTEXT

INCLUDEPATH += EMG-Diagnostics

PRECOMPILED_HEADER = pch.h

HEADERS += \
    application.h \
    pch.h \
    datasource.h \
    emgviewer.h

SOURCES += \
    application.cpp \
    datasource.cpp \
    emgviewer.cpp \
    main.cpp

RESOURCES += qml/qml.qrc

DISTFILES += \
    .log4qt.properties

TRANSLATIONS += \
    EMG-Diagnostics_en_GB.ts

# currently it's not working thus commented out
CONFIG += qmltypes
QML_IMPORT_NAME = com.github.sjacek.emgdiagnostics
QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_MINOR_VERSION = 0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

LIBS += -L$${LIB_DESTDIR} -l$${INTERFACE_LIB_NAME}

DISTFILES +=

DESTDIR = $${BIN_DESTDIR}

# Default rules for deployment.
qnx: target.path = /tmp/$${QMAKE_PROJECT_NAME}/bin
else: unix:!android: target.path = /opt/$${QMAKE_PROJECT_NAME}/bin
!isEmpty(target.path): INSTALLS += target

include( $$TOP_SRCDIR/plugins/interface/interface.pri )
