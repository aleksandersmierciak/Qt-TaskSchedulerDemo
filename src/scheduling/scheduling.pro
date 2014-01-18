QT       -= gui

TARGET = scheduling
TEMPLATE = lib

DEFINES += SCHEDULING_LIBRARY

SOURCES += \
    job.cpp \
    taskscheduler.cpp

HEADERS += \
    scheduling_global.h \
    job.h \
    taskscheduler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
