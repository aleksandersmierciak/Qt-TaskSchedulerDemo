# Add more folders to ship with the application, here
folder_01.source = qml/ui
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../scheduling/release/ -lscheduling
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../scheduling/debug/ -lscheduling
else:unix: LIBS += -L$$OUT_PWD/../scheduling/ -lscheduling

INCLUDEPATH += $$PWD/../scheduling
DEPENDPATH += $$PWD/../scheduling
