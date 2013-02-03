TEMPLATE = app

QT += testlib

include(../UseDefaults.pri)
include(../CoreLinkBase/Link.pri)
include(../CoreLinkBase/Include.pri)

TARGET = CoreLinkTest$${TARGET_SUFFIX}

test.commands = $$DESTDIR/$$TARGET
QMAKE_EXTRA_TARGETS += test
QMAKE_POST_LINK = $(MAKE) test

SOURCES += \
    ProcessTests.cpp \

