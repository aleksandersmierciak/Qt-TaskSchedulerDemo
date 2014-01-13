QT       -= gui

TARGET = scheduling
TEMPLATE = lib

DEFINES += SCHEDULING_LIBRARY

SOURCES += taskscheduler.cpp

HEADERS += taskscheduler.h\
        scheduling_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
