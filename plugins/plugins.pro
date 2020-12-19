TEMPLATE = subdirs
SUBDIRS = \
    interface \
    fake \
    sine \
    uECG

fake.depends = interface
sine.depends = interface
uECG.depends = interface
