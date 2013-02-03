# Include this .pri file to link against this library.

isEmpty(CORELINKBASE_LINK_INCLUDED) {
    CORELINKBASE_LINK_INCLUDED = yes

    include(Common.pri)
    LIBS += -L$$CORELINKBASE_DESTDIR -l$$CORELINKBASE_TARGET
    QMAKE_LFLAGS += -Wl,-rpath,$$CORELINKBASE_DESTDIR
    PRE_TARGETDEPS += $$CORELINKBASE_DESTDIR/lib$${CORELINKBASE_TARGET}.so
}

