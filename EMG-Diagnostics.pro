TEMPLATE = subdirs
SUBDIRS = \
    3rdparty/qextserialport \
    libuECG \
    libQuECG \
    libuECGpp \
    plugins \
    EMG-Diagnostics \

plugins.depends = 3rdparty/qextserialport libQuECG
EMG-Diagnostics.depends = plugins

OTHER_FILES += \
    .qmake.conf \
    .qmake.cache
