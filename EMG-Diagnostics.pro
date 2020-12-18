TEMPLATE = subdirs
SUBDIRS = \
    3rdparty/qextserialport \
    libuECG \
    plugins \
    EMG-Diagnostics \

OTHER_FILES += \
    .qmake.conf

CONFIG += ordered
