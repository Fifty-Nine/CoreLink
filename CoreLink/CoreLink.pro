TEMPLATE = lib

INCLUDEPATH += ..

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    InstructionSet.h \
    Node.h \
    Process.h \
    Program.h \

SOURCES += \
    InstructionSet.cpp \
    Node.cpp \


