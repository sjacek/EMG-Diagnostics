TEMPLATE = subdirs
SUBDIRS = \
    QtVaria \
    libuECG \
    libQuECG \
    plugins \
    EMG-Diagnostics \

libQuECG.depends = QtVaria
plugins.depends = QtVaria libQuECG
EMG-Diagnostics.depends = plugins

OTHER_FILES += \
    .qmake.conf
