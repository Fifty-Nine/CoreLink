isEmpty(COMMON_INCLUDED) { 
    COMMON_INCLUDED = yes

    CONFIG += debug_and_release 
    CONFIG(debug, debug|release) { 
        CONFIG_SUFFIX = -d
        TARGET_SUFFIX = -d
    }

    COMMON_OBJECTS_DIR = build/objs$$CONFIG_SUFFIX
    COMMON_MOC_DIR = build/mocs$$CONFIG_SUFFIX
    COMMON_UI_DIR = build/uics$$CONFIG_SUFFIX
    COMMON_RCC_DIR = build/rccs$$CONFIG_SUFFIX
    COMMON_DESTDIR = $$PWD/build

    QMAKE_CXXFLAGS += -std=c++11
}
