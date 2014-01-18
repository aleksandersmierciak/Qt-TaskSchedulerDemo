QT       -= gui

TARGET = scheduling
TEMPLATE = lib

DEFINES += SCHEDULING_LIBRARY

SOURCES += \
    job.cpp \
    machine.cpp \
    taskscheduler.cpp

HEADERS += \
    scheduling_global.h \
    job.h \
    machine.h \
    taskscheduler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
