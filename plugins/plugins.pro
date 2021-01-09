TEMPLATE = subdirs
SUBDIRS = \
    interface \
    sine \
    uECG

sine.depends = interface
uECG.depends = interface
