include(lib/hid/libhid.pri)	# libhid

HEADERS += src/delegate.h src/HIDDetailWidget.h
SOURCES += src/delegate.cc src/HIDDetailWidget.cc src/main.cc

macx {
    OBJECTS_DIR = build
}
