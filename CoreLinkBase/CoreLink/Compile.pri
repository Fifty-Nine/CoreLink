isEmpty(CORELINKBASE_CORELINK_COMPILE_INCLUDED) { 
    CORELINKBASE_CORELINK_COMPILE_INCLUDED = yes

    CORELINK_HEADERS += \
        GameSettings.h \
        InstructionSet.h \
        Node.h \
        Process.h \
        Program.h \
        Types.h \

    CORELINK_SOURCES += \
        InstructionSet.cpp \
        Node.cpp \
        Process.cpp \
        Program.cpp \

    for(header, CORELINK_HEADERS) { 
        HEADERS += $$PWD/$$header
    }

    for(source, CORELINK_SOURCES) { 
        SOURCES += $$PWD/$$source
    }
}
