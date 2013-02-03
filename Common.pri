isEmpty(COMMON_INCLUDED) { 
    COMMON_INCLUDED = yes

    COMMON_OBJECTS_DIR = build/objs
    COMMON_MOC_DIR = build/mocs
    COMMON_UI_DIR = build/uics
    COMMON_RCC_DIR = build/rccs
    COMMON_DESTDIR = $$PWD/build

    QMAKE_CXXFLAGS += -std=c++11
}
