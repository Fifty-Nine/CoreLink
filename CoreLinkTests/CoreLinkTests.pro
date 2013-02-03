TEMPLATE = app

QT += testlib

include(../UseDefaults.pri)
include(../CoreLinkBase/Link.pri)
include(../CoreLinkBase/Include.pri)

TARGET = CoreLinkTest$${TARGET_SUFFIX}

build_pass:CONFIG(debug, release|debug) { 
    test.commands = $$DESTDIR/$$TARGET
    QMAKE_EXTRA_TARGETS += test
    QMAKE_POST_LINK = $(MAKE) -f Makefile.Debug test
}
build_pass:CONFIG(release, release|debug) { 
    test.commands = $$DESTDIR/$$TARGET
    QMAKE_EXTRA_TARGETS += test
    QMAKE_POST_LINK = $(MAKE) -f Makefile.Release test
}
!build_pass { 
    test_debug.commands = $(MAKE) -f Makefile.Debug test
    test_release.commands = $(MAKE) -f Makefile.Release test
    test.commands = $(MAKE) test_debug test_release
    QMAKE_EXTRA_TARGETS += test test_debug test_release
}

SOURCES += \
    ProcessTests.cpp \

