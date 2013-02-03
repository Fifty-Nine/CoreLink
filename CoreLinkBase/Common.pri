# Include this file to configure the path variables for this library.

isEmpty(CORELINKBASE_DIR) { 
    include( ../Common.pri )
    CORELINKBASE_DIR = $$PWD
    CORELINKBASE_DESTDIR = $$COMMON_DESTDIR
    CORELINKBASE_TARGET = CoreLinkBase$$TARGET_SUFFIX
}
