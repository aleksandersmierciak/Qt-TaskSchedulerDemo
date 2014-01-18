#include "qtquick2controlsapplicationviewer.h"
#include "taskscheduler.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    TaskScheduler taskScheduler(&app);

    QtQuick2ControlsApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("taskScheduler", &taskScheduler);
    viewer.setMainQmlFile(QStringLiteral("qml/ui/main.qml"));
    viewer.show();

    return app.exec();
}
