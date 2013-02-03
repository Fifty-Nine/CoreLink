# Include this file to configure the path variables for this library.

isEmpty(CORELINKNETWORK_DIR) { 
    include( ../Common.pri )
    CORELINKNETWORK_DIR = $$PWD
    CORELINKNETWORK_DESTDIR = $$COMMON_DESTDIR
    CORELINKNETWORK_TARGET = CoreLinkNetwork$$TARGET_SUFFIX
}
