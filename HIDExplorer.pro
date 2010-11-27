include(lib/hid/libhid.pri)	# libhid

SOURCES += src/main.cc

macx {
    OBJECTS_DIR = build
}
