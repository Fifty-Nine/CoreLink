TEMPLATE = app

QT += testlib

include( ../Common.pri )

CORELINK_DIR = $$PWD/../CoreLink
CORELINK_BUILD_DIR = $$CORELINK_DIR/$$DESTDIR

LIBS += -L$$CORELINK_BUILD_DIR -lCoreLink
QMAKE_LFLAGS += -Wl,-rpath,$$CORELINK_BUILD_DIR

INCLUDEPATH += ..
DEPENDPATH += ..

test.commands = $$DESTDIR/$$TARGET
QMAKE_EXTRA_TARGETS += test

PRE_TARGETDEPS += $$CORELINK_BUILD_DIR/libCoreLink.so
POST_TARGETDEPS += test

SOURCES += \
    ProcessTests.cpp \

