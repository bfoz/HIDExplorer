include(lib/hid/libhid.pri)	# libhid

HEADERS += src/delegate.h
SOURCES += src/delegate.cc src/main.cc
HEADERS += src/ElementsWidget.h src/HIDDetailWidget.h
SOURCES += src/ElementsWidget.cc src/HIDDetailWidget.cc

macx {
    OBJECTS_DIR = build
}
