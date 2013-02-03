# Include this .pri file to link against this library.

isEmpty(CORELINKNETWORK_LINK_INCLUDED) {
    CORELINKNETWORK_LINK_INCLUDED = yes

    include(Common.pri)
    include(../CoreLinkBase/Link.pri)

    LIBS += -L$$CORELINKNETWORK_DESTDIR -l$$CORELINKNETWORK_TARGET
    QMAKE_LFLAGS += -Wl,-rpath,$$CORELINKNETWORK_DESTDIR
    PRE_TARGETDEPS += $$CORELINKNETWORK_DESTDIR/lib$${CORELINKNETWORK_TARGET}.so
}

