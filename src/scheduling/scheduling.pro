TARGET = scheduling
TEMPLATE = lib

DEFINES += SCHEDULING_LIBRARY

QT       -= gui

CONFIG += c++11

DEFINES += \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_TO_ASCII

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
