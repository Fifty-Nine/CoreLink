isEmpty(CORELINKNETWORK_CORELINK_COMPILE_INCLUDED) { 
    CORELINKNETWORK_CORELINK_COMPILE_INCLUDED = yes

    CORELINK_HEADERS += \
        Network.h \

    CORELINK_SOURCES += \
        Network.cpp \

    for(header, CORELINK_HEADERS) { 
        HEADERS += $$PWD/$$header
    }

    for(source, CORELINK_SOURCES) { 
        SOURCES += $$PWD/$$source
    }
}
