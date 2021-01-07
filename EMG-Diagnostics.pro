TEMPLATE = subdirs
SUBDIRS = \
    libuECG \
    libQuECG \
    plugins \
    EMG-Diagnostics \

plugins.depends = libQuECG
EMG-Diagnostics.depends = plugins

OTHER_FILES += \
    .qmake.conf
