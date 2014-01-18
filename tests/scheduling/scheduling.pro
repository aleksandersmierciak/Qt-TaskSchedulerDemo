QT       += testlib

QT       -= gui

TARGET = tst_schedulingtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    tst_schedulingtest.cpp \
    tst_jobtest.cpp \
    tst_machinetest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_schedulingtest.h \
    tst_jobtest.h \
    tst_machinetest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/scheduling/release/ -lscheduling
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/scheduling/debug/ -lscheduling
else:unix: LIBS += -L$$OUT_PWD/../../src/scheduling/ -lscheduling

INCLUDEPATH += $$PWD/../../src/scheduling
DEPENDPATH += $$PWD/../../src/scheduling
