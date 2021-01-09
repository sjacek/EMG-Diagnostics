INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

LIBS += -L$$TOP_BUILDDIR/libQuECG -lQuECG

INCLUDEPATH += $$TOP_SRCDIR/3rdparty/qextserialport/src
DEPENDPATH += $$TOP_SRCDIR/3rdparty/qextserialport/src
LIBS += -L$$LIB_DESTDIR -lQt5ExtSerialPort
